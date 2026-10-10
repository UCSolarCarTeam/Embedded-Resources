# Lesson 3: Bitwise Operators and Registers

Microcontroller hardware is controlled through **registers**: numbers where each bit (or group of bits) has a meaning. Controlling hardware means changing individual bits without disturbing the rest.

**Exercises:** `ex3a_bits.c`, `ex3b_fields.c`, `ex3c_registers.c`

---

## 1. Binary and hex

One hex digit is four bits. `0xA5` is `1010 0101`. Bits are numbered from the right, starting at 0:

```
bit:     7 6 5 4 3 2 1 0
0xA5:    1 0 1 0 0 1 0 1
```

## 2. The operators

| Operator | Name | What it does to a bit |
|---|---|---|
| `&` | AND | `& 0` clears, `& 1` keeps |
| `\|` | OR | `\| 1` sets, `\| 0` keeps |
| `^` | XOR | `^ 1` flips, `^ 0` keeps |
| `~` | NOT | inverts every bit |
| `<<` `>>` | shifts | move bits left / right |

Don't mix up `&` with `&&`, or `|` with `||`.

Use **unsigned** values and the `u` suffix: write `1u << 5`, not `1 << 5`.

Always add parentheses around bit tests, since `==` binds tighter than `&`:

```c
if ((status & FLAG_READY) != 0)    // correct
if (status & FLAG_READY == 1)      // wrong: means status & (FLAG_READY == 1)
```

## 3. The four idioms

For a register `reg` and bit number `n`:

```c
reg |=  (1u << n);     // set bit n
reg &= ~(1u << n);     // clear bit n
reg ^=  (1u << n);     // toggle bit n
if (reg & (1u << n))   // test bit n
```

Give bits names instead of using magic numbers:

```c
#define LED_PIN   5u
#define LED_MASK  (1u << LED_PIN)

PORT |= LED_MASK;      // LED on
PORT &= ~LED_MASK;     // LED off
```

Two useful tricks:
- `v & (v - 1)` clears the lowest set bit. Repeat until zero to count the bits.
- `v != 0 && (v & (v - 1)) == 0` tests for a power of two.

## 4. Fields

A field is several bits with one meaning, described by a **shift** (where it starts) and a **width** (how many bits).

```c
mask  = ((1u << width) - 1u) << shift;
read  = (reg >> shift) & ((1u << width) - 1u);
write = (reg & ~mask) | ((value << shift) & mask);
```

When writing a field, **clear it first**, then OR in the new value. Using only `|=` can never turn old bits off.

## 5. Hardware registers and `volatile`

A register is just a memory location at a fixed address. Vendor headers describe a peripheral as a struct:

```c
typedef struct {
    volatile uint32_t ODR;     // output data
    volatile uint32_t IDR;     // input data
} GpioRegs;

#define GPIOA ((GpioRegs *)0x48000000u)

GPIOA->ODR |= (1u << 5);       // pin 5 high
```

`volatile` tells the compiler the value can change on its own and that every read and write matters, so it must not skip or merge them. Without it, a loop like `while (!(STATUS & READY)) {}` could become an infinite loop.

In the exercises, the "hardware" is an ordinary struct in RAM, but your code is exactly what you would write for a real chip.

## 6. Registers that don't act like memory

`reg |= mask` is read, modify, write. Be careful:

- **Write-1-to-clear (W1C) flags:** writing a 1 clears that flag, and writing 0 does nothing. If you read the register, change one bit, and write it back, you also write 1 to every other flag that was set, **clearing them too**. To clear one flag, write only that flag's bit: `STATUS = ERROR_FLAG;`
- **Read-only bits** ignore writes.
- Check the chip's reference manual for the access type of every bit.

## 7. Byte order

A 16- or 32-bit value in memory is stored as bytes in some order (endianness). Build values from bytes with shifts, not by casting pointers:

```c
uint16_t v = (uint16_t)(b[0] | (b[1] << 8));    // little-endian: b[0] is the low byte
```

## Checklist

1. How do you set, clear, toggle, and test bit 5?
2. Why do you clear a field before writing it?
3. Why can `STATUS |= ERROR_FLAG` be dangerous on a write-1-to-clear register?
4. What does `volatile` do?
