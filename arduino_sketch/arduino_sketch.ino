#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6
#define WIDTH 40
#define HEIGHT 7
#define LETTER_SIZE 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(WIDTH * HEIGHT, PIN, NEO_GRB + NEO_KHZ800);

//Defines a "font" to display
//Indices 0-25 = Letters A-Z
//Index 26 = Space
byte letters[27][7] = 
{
{12,18,33,127,65,65,65},
{127,65,65,95,65,65,127},
{127,64,64,64,64,64,127},
{124,66,65,65,65,66,124},
{127,64,64,127,64,64,127},
{127,64,64,127,64,64,64},
{127,64,64,95,65,65,127},
{65,65,65,127,65,65,65},
{127,8,8,8,8,8,127},
{127,4,4,4,4,8,112},
{65,66,76,112,76,66,65},
{64,64,64,64,64,64,127},
{99,85,73,65,65,65,65},
{65,97,81,73,69,67,65},
{28,34,65,65,65,34,28},
{127,65,65,127,64,64,64},
{60,66,66,66,66,66,61},
{127,65,65,127,88,76,67},
{127,64,64,127,1,1,127},
{127,8,8,8,8,8,8},
{65,65,65,65,65,65,127},
{65,65,34,34,20,20,8},
{65,65,65,65,73,85,99},
{65,34,20,8,20,34,65},
{34,20,8,8,8,8,8},
{127,2,4,8,16,32,127},
{0,0,0,0,0,0,0},
};

//Settings for displaying the string
int stringLength = 0;
int globalOffset = 0;
byte buffer[HEIGHT][512];

//The string to display along with the color
//and the delay (smaller delay = faster horizontal scrolling).
String message = "HELLO WORLD ";
int red = 0;
int green = 255;
int blue = 0;
int delayTime = 100;

void setup()
{
 //Initialize neo pixel strip
 strip.begin();
 strip.show(); 
 
 //Clear memory
 for(int i = 0; i < HEIGHT; i++)
  for(int j = 0; j < 512; j++) buffer[i][j] = 0;
  
 //Convert letters in the string to be displayed
 for (int i = 0; i < message.length(); i++)
 {
   if (message[i] == ' ')
     setLetter(letters[26], i * LETTER_SIZE);
   else setLetter(letters[message[i] - 65], i * LETTER_SIZE);
 }
 
 stringLength = message.length();
}

void loop()
{  
 globalOffset++; //Scroll the text
 showBuffer(red, green, blue);
 delay(delayTime);
}

//Display the contents of the buffer based on the offset
void showBuffer(int r, int g, int b)
{
 strip.clear();
 
 for(int i = 0; i < HEIGHT; i++)
 {
   for(int j = 0; j < WIDTH; j++)
   {
    byte b = buffer[i][(j + globalOffset) % (stringLength * LETTER_SIZE)]; 
    if(b == 1) setLED(i, j, r, g, b);
   }
 }
 
 strip.show();
}

//Place a letter in the buffer
void setLetter(byte* letter, int offset)
{
 for(int row = 0; row < HEIGHT; row++)
 {
  int rowData = letter[row]; 
  
  //A letter is defined by the bits in each number.
  //A 0 bit means the light is off, while a 1 bit means
  //that it is on.
  for(int i = 0; i < 7; i++)
  {
    byte b = bitRead(rowData, 7 - i - 1);
    buffer[row][i + offset] = b;
  }
  
 } 
}

//Turn on an LED with a given color at a specified row and column
void setLED(int row, int col, int r, int g, int b)
{
 strip.setPixelColor(getIndex(row, col), strip.Color(r, g, b));
}

//Convert co-ordinates to an index since the grid
//is made up of multiple connected neo pixel strips.
int getIndex(int row, int col)
{
 return row * WIDTH + col; 
}
