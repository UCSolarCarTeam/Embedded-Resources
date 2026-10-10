/*
 * Exercise 4c - State machines   (Lesson 4, section 3)
 *
 * Part A: an event-driven state machine (a door).
 * Part B: a time-driven state machine (a traffic light).
 *     gcc -Wall -I. Lesson4/ex4c_state_machine.c -o ex4c && ./ex4c
 */
#include <stdint.h>
#include "test.h"

/* ---- Part A: a door ----
 * Transitions (anything not listed means "stay in the same state"):
 *
 *   CLOSED + OPEN   -> OPEN
 *   CLOSED + LOCK   -> LOCKED
 *   OPEN   + CLOSE  -> CLOSED
 *   LOCKED + UNLOCK -> CLOSED
 *
 * So a locked door ignores EVT_OPEN, and an open door can't be locked.
 */
typedef enum { DOOR_CLOSED, DOOR_OPEN, DOOR_LOCKED } DoorState;
typedef enum { EVT_OPEN, EVT_CLOSE, EVT_LOCK, EVT_UNLOCK } DoorEvent;

/* Return the new state after `event` happens in `state`. */
DoorState door_next(DoorState state, DoorEvent event)
{
    return DOOR_LOCKED; /* TODO */
}

/* ---- Part B: a traffic light ----
 * The light has a state and a count of ticks left in that state.
 *   RED lasts 4 ticks, then GREEN lasts 3 ticks, then YELLOW lasts 1 tick,
 *   then back to RED, and so on.
 */
typedef enum { LIGHT_RED, LIGHT_GREEN, LIGHT_YELLOW } Light;

#define RED_TICKS     4
#define GREEN_TICKS   3
#define YELLOW_TICKS  1

typedef struct {
    Light    state;
    unsigned ticks_left;
} TrafficLight;

/* Start the light at RED with RED_TICKS ticks left. */
void tl_init(TrafficLight *t)
{
    /* TODO */
}

/* One tick of time passes. Subtract 1 from ticks_left. If it reaches 0,
 * move to the next state and set ticks_left for that new state. */
void tl_tick(TrafficLight *t)
{
    /* TODO */
}

/* ---- TESTS (do not edit below) ---- */
int main(void)
{
    SECTION("door_next: valid transitions");
    CHECK_EQ(door_next(DOOR_CLOSED, EVT_OPEN), DOOR_OPEN);
    CHECK_EQ(door_next(DOOR_CLOSED, EVT_LOCK), DOOR_LOCKED);
    CHECK_EQ(door_next(DOOR_OPEN, EVT_CLOSE), DOOR_CLOSED);
    CHECK_EQ(door_next(DOOR_LOCKED, EVT_UNLOCK), DOOR_CLOSED);

    SECTION("door_next: events that do nothing");
    CHECK_EQ(door_next(DOOR_CLOSED, EVT_CLOSE), DOOR_CLOSED);
    CHECK_EQ(door_next(DOOR_CLOSED, EVT_UNLOCK), DOOR_CLOSED);
    CHECK_EQ(door_next(DOOR_OPEN, EVT_OPEN), DOOR_OPEN);
    CHECK_EQ(door_next(DOOR_OPEN, EVT_LOCK), DOOR_OPEN);
    CHECK_EQ(door_next(DOOR_OPEN, EVT_UNLOCK), DOOR_OPEN);
    CHECK_EQ(door_next(DOOR_LOCKED, EVT_OPEN), DOOR_LOCKED);
    CHECK_EQ(door_next(DOOR_LOCKED, EVT_CLOSE), DOOR_LOCKED);
    CHECK_EQ(door_next(DOOR_LOCKED, EVT_LOCK), DOOR_LOCKED);

    SECTION("door_next: a whole sequence");
    {
        DoorState s = DOOR_CLOSED;
        s = door_next(s, EVT_OPEN);    CHECK_EQ(s, DOOR_OPEN);
        s = door_next(s, EVT_CLOSE);   CHECK_EQ(s, DOOR_CLOSED);
        s = door_next(s, EVT_LOCK);    CHECK_EQ(s, DOOR_LOCKED);
        s = door_next(s, EVT_OPEN);    CHECK_EQ(s, DOOR_LOCKED);   /* ignored */
        s = door_next(s, EVT_UNLOCK);  CHECK_EQ(s, DOOR_CLOSED);
    }

    SECTION("tl_init");
    {
        TrafficLight t = { LIGHT_YELLOW, 99 };
        tl_init(&t);
        CHECK_EQ(t.state, LIGHT_RED);
        CHECK_EQ(t.ticks_left, RED_TICKS);
    }

    SECTION("tl_tick: one full cycle (8 ticks)");
    {
        /* state and ticks_left expected AFTER each tick */
        const Light     want_state[8] = { LIGHT_RED, LIGHT_RED, LIGHT_RED, LIGHT_GREEN,
                                          LIGHT_GREEN, LIGHT_GREEN, LIGHT_YELLOW, LIGHT_RED };
        const unsigned  want_left[8]  = { 3, 2, 1, 3, 2, 1, 1, 4 };
        TrafficLight t;
        tl_init(&t);
        for (int i = 0; i < 8; i++) {
            tl_tick(&t);
            CHECK_EQ(t.state, want_state[i]);
            CHECK_EQ(t.ticks_left, want_left[i]);
        }
        tl_tick(&t);                              /* second cycle starts the same way */
        CHECK_EQ(t.state, LIGHT_RED);
        CHECK_EQ(t.ticks_left, 3);
    }

    return report();
}
