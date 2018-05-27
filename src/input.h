#ifndef _INPUT_H
#define _INPUT_H

/** Returns data about a press
  * if return = 0 no press has ocurred
  * if return = 1 user pressed screen
  * if return = 2 user released screen
  * if return = 3 a key was pressed
  */
int input_handle();

#endif // _INPUT_H
