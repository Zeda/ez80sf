# ez80sf
This is a library of single-precision floating-point routines for the eZ80.

## How to use.
You'll need [**fasmg**](https://github.com/jacobly0/fasmg-ez80) to compile these routines,
which are located in the [**/src**](/src) folder. Routines are named __fp**xxxx**.
For example, `__fpmul` refers  to the floating-point multuplication routine.

## Contributing
Honestly, I still don't understand jacobly's test environment very well, so I can't
add suggestions about that. However, float routines should follow some basic rules:
* The first operand is in AUBC
* The second operand is in EUHL
* Output is in AUBC
* If a routine doesn't require an argument, it must be preserved. For example, __fpln
  only takes one argument, so EUHL should be preserved.
* Names of float routines should start with `__fp` and end with a short name indicating
  what the routine is. For example, `__fpneg` negates the input float.
