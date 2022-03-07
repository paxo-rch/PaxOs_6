#ifndef COLOR_HPP
#define COLOR_HPP

/*###############################################*/
/*              theme configuration              */
/*###############################################*/

#define THEME_BLACK 0
#define THEME_BLUE 1
#define THEME_GREEN 2
#define THEME_RED 3
#define THEME_YELLOW 4
#define THEME_WHITE 5
#define THEME_CONTRAST 6    // hight constrast

color_t theme_color[][]=
{   // color, background color, border color
    {0xFFFF, 0x4A69, 0xC638},   // black
    {0xFFFF, 0x22B5, 0x4800},   // blue
    {0xFFFF, 0x3C42, 0x4800},   // green
    {0x0000, 0x7841, 0x4800},   // red
    {0x0000, 0xFFC8, 0xEF37},   // yellow
    {0x0000, 0xFFFF, 0xBDF7},   // white
    {0xFFFF, 0x0000, 0xFFFF}    // contrast
};

/*###############################################*/
/*             alignement configuration          */
/*###############################################*/

#define LEFT_ALIGNMENT 0
#define RIGHT_ALIGNMENT 1
#define CENTER_ALIGNMENT 2

/*###############################################*/
/*             graphics configuration            */
/*###############################################*/

#define DEFAULT_THEME THEME_GREEN
#define DEFAULT_BORDER_SIZE 1
#define DEFAULT_ALIGNEMENT LEFT_ALIGNMENT
#define DEFAULT_RADIUS 15


#endif