/*
 * ledMatrixDriver.c
 *
 *  Created on: 27. 4. 2019
 *      Author: lukelee36
 */

#include "ledMatrixDriver.h"
#include <ti/drivers/GPIO.h>
#include "Board.h"
#include <stdio.h>
#include <string.h>

// for one color
static unsigned int rows1[NUMROWS][NUMROWPIXEL] = { 0 };
static unsigned int rows2[NUMROWS][NUMROWPIXEL] = { 0 };

//get ready for RGB
static unsigned int rows1R[NUMROWS][NUMROWPIXEL] = { 0 };
static unsigned int rows1G[NUMROWS][NUMROWPIXEL] = { 0 };
static unsigned int rows1B[NUMROWS][NUMROWPIXEL] = { 0 };

//memset(row1, 0, sizeof(row1));
//memset(row2, 0, sizeof(row2));

void lmd_show_char(uint8_t position, int rows, int character, int color[])
{
    int i,j;
    for (i = 0; i < NUMROWS; ++i)
    {
        for (j = 0; j < ENDROWS; ++j)
        {
            if(rows == ROWS1)
            {
                if(color[0])
                {
                    memcpy(&rows1R[i][j+1+(position*5)], &Malphabet[i][j+(character*5)], sizeof(unsigned int));
                }
                if(color[1])
                {
                    memcpy(&rows1G[i][j+1+(position*5)], &Malphabet[i][j+(character*5)], sizeof(unsigned int));
                }
                if(color[2])
                {
                    memcpy(&rows1B[i][j+1+(position*5)], &Malphabet[i][j+(character*5)], sizeof(unsigned int));
                }

            }

            if(rows == ROWS2)
            {
                memcpy(&rows2[i][j+1+(position*5)], &Malphabet[i][j+(character*5)], sizeof(unsigned int));
            }
        }
    }
}


void lmd_show_char_a(uint8_t position, int rows)
{
    int i,j;
    for (i = 0; i < NUMROWPIXEL; ++i)
    {
        for (j = 0; j < ENDROWS; ++j)
        {
            if(rows == ROWS1)
            {
                memcpy(&rows1[i][j+1+(position*5)], &Malphabet[i][j], sizeof(unsigned int));
            }

            if(rows == ROWS2)
            {
                memcpy(&rows2[i][j+1+(position*5)], &Malphabet[i][j], sizeof(unsigned int));
            }
        }
    }
}

void loadMatrixData(uint8_t addr)
{
    int j;

    //lmd_demo_alphabeth();
    int color[] = {1,1,0};

     lmd_show_text("aloho  mora",color);
   // lmd_show_text_scroll("lol_____", ROWS1, color);
   // lmd_sho_text_scroll("Nazdar zmrdi tak co jak to jde", ROWS2);

    for(j = 0; j < NUMROWPIXEL; j++)
    {
        //setup for writing color to displey
        lmd_write_pixel(R1Matrix, rows1R[addr][j]);
        lmd_write_pixel(R2Matrix, rows1G[addr][j]);
        //lmd_write_pixel(B1Matrix, rows1B[addr][j]);

        //lmd_write_pixel(R2Matrix, rows2[addr][j]);
        //GPIO_write(R1Matrix, row1[addr][j]);
        //GPIO_write(R2Matrix, row2[addr][j]);
//      GPIO_write(R2Matrix, ptr[j]);
        GPIO_write(CLKMatrix, tick);
       // usleep(100);

        GPIO_write(CLKMatrix, toc);
    }
}

void lmd_write_pixel(int pinRow, unsigned int data)
{
    if(data)
    {
        GPIO_write(pinRow, ONLED);
    }
    else
    {
        GPIO_write(pinRow, OFFLED);
    }
}

void lmd_demo_alphabeth(void)
{
    static int counter = 0;

    if(counter < 500)
    {
        lmd_demo_alphabeth_list(0);
    }
    else if(counter < 1000)
    {
        lmd_demo_alphabeth_list(1);
    }
    else
    {
        lmd_demo_alphabeth_list(2);

    }
    counter++;

    if(counter == 3000)
    {
        counter = 0;
    }
}


void lmd_demo_alphabeth_list(int list)
{
    int i = list;
    int j = 0;
    int color[] = {1,1,0};
    for(j; j<MAXDISPCHAR; j++)
    {
        if(j<6)
        {
            lmd_show_char(j, ROWS1, j+(i*MAXDISPCHAR), color);
        }
        else
        {
            lmd_show_char(j-6, ROWS2, j+(i*MAXDISPCHAR), color);
        }
    }
}

void lmd_show_text(char text[], int color[])
{
    // this is part where I want to parse text to character
    /**
     * also  this function will crop text to fit it into displey,
     * in this aplication I have 6 characters on one part of displey
    */
    int max = strlen(text);
    int i;

    // This crop text to 12 char
    if(max>MAXDISPCHAR)
    {
        max = MAXDISPCHAR;
    }

    // if i is bigger than 6 it will automaticaly next character write to bottom part of displey
    for (i = 0; i < max; ++i)
    {
        if(i<6)
        {
            lmd_find_char(text[i], ROWS1, i, color);
        }
        else
        {
            lmd_find_char(text[i], ROWS2, i-6, color);
        }
    }
}

void lmd_show_text_scroll(char text[], int rows, int color[])
{

    int max = strlen(text);
    int i;
    static int counter = 0;

    static int positions = ENDROWS;

    //positions = positions + max;
    if(counter==150)
    {
        positions = positions - 1;
        counter = 0;
    }

    if(positions+max <= BEGINROWS)
    {
        lmd_null_rows(rows, color);
        positions = ENDROWS;
    }

    //lmd_show_char(position + 1, rows, NULLCHAR);

    for(i = 0; i < max; i++)
    {
        if((positions+i)<6 && (positions+i)>=0)
        {
            lmd_find_char(text[i], rows, positions+i, color);
            //lmd_show_char(positions+i+1, rows, NULLCHAR);
        }
    }

    counter++;
}

void lmd_find_char(char character, int rows, int position, int color[])
{
    // this is the part where I count number from ascii to my alphabeth with 36 char since number 0-9
   // int ch = atoi(character);
    // A == 65, Z == 90, 0 == 48, 9 == 57
    if(character>='a' && character<='z')
    {
        character = toupper(character);
    }

    if(character>='A' && character<='Z')
    {
        lmd_show_char(position, rows, character-CHAROFFSET,color);
    }
    else if(character>='0' && character<='9')
    {
        lmd_show_char(position, rows, character-NUMBEROFFSET, color);
    }
    else
    {
        lmd_show_char(position, rows, NULLCHAR, color);
    }
}

void lmd_null_rows(int rows, int color[])
{
    int i;
    for(i = 0; i<ENDROWS; i++)
    {
        lmd_show_char(i, rows, NULLCHAR, color);
    }
}
