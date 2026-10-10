# Lesson 2: Pointers, Arrays, and Strings

Pointers let you work with buffers, hardware registers, and function arguments efficiently. They are also the most common source of crashes, so we focus on using them safely.

**Exercises:** `ex2a_pointers.c`, `ex2b_arrays.c`, `ex2c_strings.c`

---

## 1. Pointers

A pointer holds a memory address.

```c
uint8_t value = 42;
uint8_t *p = &value;    // p holds the address of value
*p = 43;                // follow the pointer: value is now 43
```

| Syntax | Meaning |
|---|---|
| `&x` | address of `x` |
| `*p` | the value `p` points to |
| `p->field` | field of the struct `p` points to |

`NULL` means "points to nothing". Never dereference it; check first if it might be NULL.

## 2. Passing by pointer

C passes arguments by copy. To let a function change the caller's variable, or return several results, pass a pointer:

```c
void swap(uint8_t *a, uint8_t *b)
{
    uint8_t tmp = *a;
    *a = *b;
    *b = tmp;
}

swap(&x, &y);
```

Use `const` for data the function only reads: `uint16_t checksum(const uint8_t *buf, size_t len);`

## 3. Arrays

```c
uint8_t buf[16];               // 16 bytes (garbage if local!)
uint8_t zeros[16] = {0};       // all zero
```

- Indexes run from 0 to N-1. **C does not check bounds.** Writing `buf[16]` silently corrupts memory.
- When you pass an array to a function it becomes a pointer and **the length is lost**. Always pass the length separately.
- `arr[i]` is the same as `*(arr + i)`. Adding 1 to a pointer moves it by one *element*.

## 4. Strings

A string is a `char` array that ends with the special character `'\0'` (the number 0). That marks where the text stops. There is no separate length: to find the end, you look for the `'\0'`.

```c
char word[] = "Hi";     // 3 bytes: 'H', 'i', '\0'
```

**Looping over a string** is the pattern you will use for almost everything:

```c
for (size_t i = 0; word[i] != '\0'; i++) {
    // word[i] is the character at position i
}
```

Things to remember:

- A buffer needs **one extra byte** for the `'\0'`. `"Hello"` needs 6 bytes.
- Compare strings with `strcmp(a, b)`, not `==`. The `==` operator only compares addresses, not the text.
- Don't write past the end of a buffer. Always know how big it is. `snprintf(buf, sizeof buf, ...)` is a safe way to fill one.

### ASCII: characters are just numbers

A computer can only store numbers, so each character is stored as a number. The agreed-upon list that says which number means which character is called **ASCII**. It has 128 entries (0 to 127), so every character fits in one byte.

You can see this in C. A `char` holds a number, and the same value can be printed either way:

```c
char c = 'A';
printf("%c\n", c);    // prints the character:  A
printf("%d\n", c);    // prints the number:     65
```

A string is just a row of these numbers. The string `"Hi"` is stored in memory as three bytes:

```
'H'   'i'   '\0'
 72   105    0
```

This is why the `'\0'` terminator is simply the number 0.

The parts of the table you will use most:

| Characters | Numbers | In hex |
|---|---|---|
| `'\0'` (end of string) | 0 | 0x00 |
| `'\n'` (newline) | 10 | 0x0A |
| `'\r'` (carriage return) | 13 | 0x0D |
| `' '` (space) | 32 | 0x20 |
| `'0'` to `'9'` | 48 to 57 | 0x30 to 0x39 |
| `'A'` to `'Z'` | 65 to 90 | 0x41 to 0x5A |
| `'a'` to `'z'` | 97 to 122 | 0x61 to 0x7A |

This is only the part you need most often. You can look up the full ASCII table here: https://www.ascii-code.com/

The important thing is that the digits, the uppercase letters, and the lowercase letters are each **in order, with no gaps**. That is what makes these tricks work:

**Digit character to number.** `'0'` is 48, `'1'` is 49, and so on, so subtracting `'0'` gives the digit's value:

```c
int digit = '7' - '0';        // 55 - 48 = 7
```

**Number to digit character.** Add `'0'` going the other way:

```c
char c = 7 + '0';             // 7 + 48 = 55, which is '7'
```

**Lowercase to uppercase.** `'a'` (97) and `'A'` (65) are 32 apart, and so is every other letter pair:

```c
char upper = c - ('a' - 'A'); // 'a' - 32 is 'A'
```

You should not memorize the numbers. Write `'0'`, `'a'`, and `'A'` in your code instead of 48, 97, and 65. The code is easier to read and the compiler fills in the numbers for you.

**Check the range first.** Only convert a character if it is in the right group:

```c
if (c >= '0' && c <= '9') { ... }   // c is a digit
if (c >= 'a' && c <= 'z') { ... }   // c is a lowercase letter
if (c >= 'A' && c <= 'Z') { ... }   // c is an uppercase letter
```

**Good to know**
- Some ASCII values (0 to 31) are not printable. They are control codes, like `'\n'` for a new line. `'\0'` is one of them.
- ASCII only covers English letters, digits, and punctuation. Accented letters and other languages use other encodings (such as UTF-8, which uses more than one byte per character). Most embedded code just sticks to plain ASCII.
- For the curious: `'a'` and `'A'` differ by exactly one bit (bit 5, the value 32). Lesson 3 covers bits, and you can then see that flipping bit 5 switches a letter's case.

## Checklist

1. What is the size of `uint8_t buf[16]` as a function parameter, and why?
2. If `uint32_t *p` holds address 0x1000, what is `p + 3`?
3. How many bytes does `"Hello"` need?
4. How do you turn the character `'7'` into the number 7?
5. Why must a function that fills a buffer be told its size?
