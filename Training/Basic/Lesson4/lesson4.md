# Lesson 4: Structs, Enums, and State Machines

Real firmware keeps track of what it is doing: is the door open, is the button pressed, is the light red? Structs, enums, and state machines are the tools for that.

**Exercises:** `ex4a_structs.c`, `ex4b_enums.c`, `ex4c_state_machine.c`

---

## 1. Structs

A struct groups related values into one thing:

```c
typedef struct {
    uint8_t id;
    int16_t temp_c10;     // 253 means 25.3 C
    uint8_t humidity;
} Reading;
```

`typedef` lets you write `Reading` instead of `struct Reading`.

Create one and use its fields with a dot:

```c
Reading r = { 7, 253, 40 };    // id, temp_c10, humidity (in that order)
r.temp_c10 = 260;
```

**Through a pointer, use `->`.** This is the same as the dot, but for a pointer to a struct:

```c
void set_temp(Reading *r, int16_t t)
{
    r->temp_c10 = t;           // same as (*r).temp_c10 = t;
}

set_temp(&r, 270);
```

Pass structs by pointer when a function needs to change them (or when they are large). Use `const Reading *` when it only reads.

**Arrays of structs** work like any other array:

```c
Reading readings[3];
readings[0].temp_c10 = 200;
```

(In Lesson 3 you already used a struct for hardware registers: `g->ODR |= ...`)

## 2. Enums

An enum is a list of named constants. They are numbered 0, 1, 2, ... automatically:

```c
typedef enum {
    LED_OFF,        // 0
    LED_ON,         // 1
    LED_BLINK       // 2
} LedMode;
```

Use them instead of "magic numbers". `mode = LED_BLINK;` is much clearer than `mode = 2;`.

A `switch` is the natural way to act on an enum:

```c
const char *name(LedMode m)
{
    switch (m) {
    case LED_OFF:   
        return "OFF";
    case LED_ON:    
        return "ON";
    case LED_BLINK: 
        return "BLINK";
    default:        
        return "UNKNOWN";
    }
}
```

Two tips:
- Always add a `default:` for unexpected values.
- Remember `break;` at the end of each case if you don't `return` (otherwise execution "falls through" into the next case).

## 3. State machines

A **state machine** is a program that is always in exactly one **state**, and moves to another state when something happens (an **event**). Door example:

```
            OPEN
   CLOSED ---------> OPEN
          <---------
            CLOSE

   CLOSED --LOCK--> LOCKED --UNLOCK--> CLOSED
```

In code, store the state in a variable and use a `switch` on it:

```c
typedef enum { DOOR_CLOSED, DOOR_OPEN } DoorState;
typedef enum { EVT_OPEN, EVT_CLOSE } DoorEvent;

DoorState door_next(DoorState state, DoorEvent event)
{
    switch (state) {
    case DOOR_CLOSED:
        if (event == EVT_OPEN) return DOOR_OPEN;
        break;
    case DOOR_OPEN:
        if (event == EVT_CLOSE) return DOOR_CLOSED;
        break;
    }
    return state;      // any other event: stay in the same state
}
```

Notice the last line: an event that does not apply in the current state is simply ignored.

Steps to build any state machine:
1. List the states.
2. List the events.
3. For each state, decide which events cause which change. (A small table on paper helps.)
4. Write one `switch` on the state.

**Time-driven state machines** use a "tick" (called at a regular interval) instead of events. A traffic light is the classic example: it counts ticks, and when the count reaches zero it moves to the next state. Combine a struct and an enum to hold everything:

```c
typedef struct {
    Light    state;
    unsigned ticks_left;
} TrafficLight;
```

State machines keep firmware predictable: at any moment you know exactly what state you are in, and every change is written down in one place.

## Checklist

1. When do you use `.` and when do you use `->`?
2. What number is `LED_BLINK` in the enum above?
3. Why add a `default:` to a `switch`?
4. In a state machine, what should happen if an event doesn't apply to the current state?
