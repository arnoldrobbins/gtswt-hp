


expression (gpst)
int *gpst;
{
  extern int symbol;
  int getsym();
  int state;
  do {
     constant (& state);
     switch (state) {
        case FAILURE: {
           *gpst = FAILURE;
           return;
           }
        }
     if (state == NOMATCH) {
        command (& state);
        switch (state) {
           case FAILURE: {
              *gpst = FAILURE;
              return;
              }
           }
        }
     } while (state == ACCEPT);
  switch (state) {
     case NOMATCH: {
        state = ACCEPT;
        break;
        }
     }
  if (state == ACCEPT) {
     state = NOMATCH;
     if (symbol == NEWLINE) {
        state = ACCEPT;
        }
     if (state == NOMATCH) {
        if (symbol == EOS) {
           state = ACCEPT;
           }
        else {
           fprintf (stderr, "%c: unrecognized command\n", symbol);
           }
        }
     if (state != ACCEPT) {
        *gpst = FAILURE;
        return;
        }
     }
  *gpst = state;
}



constant (gpst)
int *gpst;
{
  extern int symbol;
  int getsym();
  int state;
  double ctod();
  while (symbol == ' ' || symbol == '\t')
     getsym();
  state = NOMATCH;
  if (symbol == '.') {
     state = ACCEPT;
     push (ctod (line, & scanptr));
     scanptr--;
     getsym ();
     }
  if (state == NOMATCH) {
     if ('0' <= symbol && symbol <= '9') {
        state = ACCEPT;
        push (ctod (line, & scanptr));
        scanptr--;
        getsym ();
        }
     }
  *gpst = state;
}



command (gpst)
int *gpst;
{
  extern int symbol;
  int getsym();
  int state;
  int i;
  int sound();
  double pow(), fmod();
  while (symbol == ' ' || symbol == '\t')
     getsym();
  state = NOMATCH;
  if (symbol == 'p') {
     state = ACCEPT;
     if (sound (1))
        printf ("%1.1lf\n", stack [sp]);
     getsym ();
     }
  if (state == NOMATCH) {
     if (symbol == 'P') {
        state = ACCEPT;
        for (i = 1; i < sp; i++)
           printf ("%1.1lf\n", stack [i]);
        getsym ();
        }
     if (state == NOMATCH) {
        if (symbol == '+') {
           state = ACCEPT;
           if (sound (2)) {
              stack [sp - 1] += stack [sp];
              sp--;
              }
           getsym ();
           }
        if (state == NOMATCH) {
           if (symbol == '-') {
              state = ACCEPT;
              if (sound (2)) {
                 stack [sp - 1] -= stack [sp];
                 sp--;
                 }
              getsym ();
              }
           if (state == NOMATCH) {
              if (symbol == '*') {
                 state = ACCEPT;
                 if (sound (2)) {
                    stack [sp - 1] *= stack [sp];
                    sp--;
                    }
                 getsym ();
                 }
              if (state == NOMATCH) {
                 if (symbol == '/') {
                    state = ACCEPT;
                    if (sound (2)) {
                       stack [sp - 1] /= stack [sp];
                       sp--;
                       }
                    getsym ();
                    }
                 if (state == NOMATCH) {
                    if (symbol == '%') {
                       state = ACCEPT;
                       if (sound (2)) {
                          stack [sp - 1] = fmod (stack [sp - 1], stack[sp]);
                          sp--;
                       }
                       getsym ();
                       }
                    if (state == NOMATCH) {
                       if (symbol == '^') {
                          state = ACCEPT;
                          if (sound (2)) {
                             stack [sp - 1] = pow (stack [sp - 1], stack [sp]);
                             sp--;
                             }
                          getsym ();
                          }
                       if (state == NOMATCH) {
                          if (symbol == 'd') {
                             state = ACCEPT;
                             if (sound (1))
                                sp--;
                             getsym ();
                             }
                          if (state == NOMATCH) {
                             if (symbol == 'D') {
                               state = ACCEPT;
                               sp = 0;
                               getsym ();
                               }
                             if (state == NOMATCH) {
                               if (symbol == '<') {
                               state = ACCEPT;
                               if (sound (2)) {
                                  if (stack [sp - 1] < stack [sp])
                                     stack [sp - 1] = 1.0;
                                  else
                                     stack [sp - 1] = 0.0;
                                  sp--;
                                  }
                               getsym ();
                               }
                               if (state == NOMATCH) {
                               if (symbol == '=') {
                               state = ACCEPT;
                               if (sound (2)) {
                                  if (stack [sp - 1] == stack [sp])
                                     stack [sp - 1] = 1.0;
                                  else
                                     stack [sp - 1] = 0;
                                  sp--;
                                  }
                               getsym ();
                               }
                               if (state == NOMATCH) {
                               if (symbol == '>') {
                               state = ACCEPT;
                               if (sound (2)) {
                                  if (stack [sp - 1] > stack [sp])
                                     stack [sp - 1] = 1.0;
                                  else
                                     stack [sp - 1] = 0.0;
                                  sp--;
                                  }
                               getsym ();
                               }
                               if (state == NOMATCH) {
                               if (symbol == '&') {
                               state = ACCEPT;
                               if (sound (2)) {
                                  if (stack [sp - 1] != 0.0 && stack [sp] != 0.0)
                                     stack [sp - 1] = 1.0;
                                  else
                                     stack [sp - 1] = 0.0;
                                  sp--;
                                  }
                               getsym ();
                               }
                               if (state == NOMATCH) {
                               if (symbol == '|') {
                               state = ACCEPT;
                               if (sound (2)) {
                                  if (stack [sp - 1] != 0.0 || stack [sp] != 0.0)
                                     stack [sp - 1] = 1.0;
                                  else
                                     stack [sp - 1] = 0.0;
                                  sp--;
                                  }
                               getsym ();
                               }
                               if (state == NOMATCH) {
                               if (symbol == '!') {
                               state = ACCEPT;
                               if (sound (1))
                                  if (stack [sp] != 0.0)
                                     stack [sp] = 0.0;
                                  else
                                     stack [sp] = 1.0;
                               getsym ();
                               }
                               if (state == NOMATCH) {
                               if (symbol == 'q') {
                               state = ACCEPT;
                               exit (0);
                               getsym ();
                               }
                               if (state == NOMATCH) {
                               if (symbol == 'Q') {
                               state = ACCEPT;
                               exit (0);
                               getsym ();
                               }
                               }
                               }
                               }
                               }
                               }
                               }
                               }
                               }
                             }
                          }
                       }
                    }
                 }
              }
           }
        }
     }
  *gpst = state;
}
