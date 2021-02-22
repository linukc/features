[Examples](https://zen.yandex.ru/media/id/5f33070dfb3f292f3d71ac2f/otladka-python-s-pomosciu-pdb-5f4a3691aec899427dfdadf7?utm_source=serp)

python -m pdb test.py
[equal to import pdb; pdb.set_trace() or Python 3.7+ breakpoint()]
1. Navigation
  - n (next): one step
  - s (step): step into
  - u/d (up, down): movements along the stack 
  - j <line>(jump): jump to line of code
2. Orientation
  - l (list): show 10 lines of code
  - source <object>: show instanse of module, class, method, function ...
  - w (where): show current position in stack
3. Entity
  - args (a): print args
  - p (print): print value
  - pp: pretty print
  - return (r): end the function
  - retval (rv): end the function and print value
  - whatis <name>: display type
  - display <name> / undisplay <name>: print value each time (mb for loop useful)
 4. Execute
  - !<code>: perform code
  - interacte: interactive mode (ctrl+D for exit())
 5. Breakpoints (bp)
  - b: show list of breakpoints
  - b <line>: set breakpoint
  - c (continue): jump to next breakpoint
  - clear <id of bp>: delete certain bp
  - enable/ disable: switch bp behavior
