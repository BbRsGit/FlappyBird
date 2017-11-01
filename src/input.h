#ifndef _INPUT_H
#define _INPUT_H

struct press
    {
    int x;
    int y;
    int is_pressed;
    };

/** Returns data about a press
  * if pressed = 0 no press has ocurred
  * if pressed = 1 user pressed screen
  * if pressed = 2 user released screen
  */
void input_handle(struct press* press);

#endif // _INPUT_H
