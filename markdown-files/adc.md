# Analog-to-Digital Converter (ADC)
----
## Signals
A **signal** is a detectable physical quantity (e.g. voltage, current, etc.) by which information can be transmitted.

There are two standard frameworks used to view and analyze of signals: 

- **continuous-time**:  time variations are considered on an infinitesimal scale
- **discrete-time**: time variations are considered in discrete steps

![Alt text](../images/cont-time.jpeg)

Examples of continuous variables: temperature, distance, etc.

Examples of discrete variables: ice cream flavours, number of people, etc.


The real world is analog, but our microcontroller is digital!

## Digital vs Analog

An **analog** signal refers to a continuously-valued signal, meanwhile…

A **digital** signal refers to a discretely-valued signal, where its magnitude is determined by quantization of each discrete point in time

- **quantization** assigns a single number to represent a range of magnitudes of a continuous signal

The world is often analog, but our microcontrollers can only operate with discrete values…

So how do we resolve this?

## Analog-to-Digital Converter (ADC)

We can convert the analog to a digital representation by using sampling.

Sampling is measuring the signal at a periodic rate.

ADD IMAGE HERE !!

- talk abt resolution i guess lol