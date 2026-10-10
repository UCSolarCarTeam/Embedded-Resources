# Lesson 1: Variables and Data Types

On a microcontroller, memory is small and registers have exact sizes, so you need to know how big your numbers are.

**Exercises:** `ex1a_fixed_width.c`, `ex1b_predict.c`, `ex1c_scaling.c`

---

## 1. Fixed-width types

The size of `int` depends on the chip (16 bits on AVR, 32 on ARM). Use `<stdint.h>` when size matters:

| Type | Bits | Range |
|---|---|---|
| `uint8_t` / `int8_t` | 8 | 0 to 255 / -128 to 127 |
| `uint16_t` / `int16_t` | 16 | 0 to 65,535 / -32,768 to 32,767 |
| `uint32_t` / `int32_t` | 32 | 0 to about 4.29 billion / about +/- 2.1 billion |

Use `bool` from `<stdbool.h>` for true/false, and `size_t` for sizes and array lengths.

Rules of thumb:
- Registers, protocol fields, raw bytes: use the exact-width type.
- Plain counters and loops: `int` or `unsigned` is fine.
- Use unsigned for bit patterns, signed for values that can go negative.

## 2. Overflow

Unsigned values **wrap around**:

```c
uint8_t x = 255;
x = x + 1;      // 0
uint8_t y = 0;
y = y - 1;      // 255
```

Signed overflow is **undefined behavior**: never rely on it.

Check before adding: `if (a > UINT32_MAX - b)` means `a + b` would overflow.

**Saturating** arithmetic stops at the limit instead of wrapping:

```c
unsigned sum = (unsigned)a + b;
return (sum > 255) ? 255 : (uint8_t)sum;
```

## 3. Promotion and conversion

Anything smaller than `int` is converted to `int` before arithmetic:

```c
uint8_t a = 200, b = 100;
int     s1 = a + b;      // 300
uint8_t s2 = a + b;      // 44 (300 doesn't fit in 8 bits)
```

Mixing signed and unsigned of the same size converts the signed value to unsigned:

```c
uint32_t u = 5;
int32_t  s = -10;
if (u + s > 0) { }       // TRUE! s becomes a huge unsigned number
```

When you need extra room, widen **before** the operation: `(uint32_t)a * b`, not `(uint32_t)(a * b)`.

## 4. Division

- Integer division drops the fraction: `7 / 2 == 3`, `-7 / 2 == -3`.
- Never divide by zero.

## 5. Scaled integers instead of floats

Many microcontrollers have no floating-point unit, so floats are slow. Use scaled integers:

- Store 25.3 C as `253` (tenths of a degree).
- Store voltages in millivolts.

```c
// 12-bit ADC (0..4095), 3300 mV reference
uint32_t mv = ((uint32_t)adc * 3300u) / 4095u;   // widen BEFORE multiplying
```

Always check the largest possible intermediate value against the type's maximum.

## 6. `const`, `static`, `volatile`

- `const`: read-only. A `static const` table can live in flash instead of RAM.
- `static` inside a function: keeps its value between calls. `static` at file level: private to that file.
- `volatile`: the value can change behind the compiler's back (hardware register, interrupt). Every access really happens. See Lesson 3.

## Checklist

1. What are the ranges of `uint8_t` and `int8_t`?
2. What does `uint8_t x = 250; x += 10;` give?
3. Why is `(uint32_t)a * b` safer than `(uint32_t)(a * b)` for `uint16_t` values?
