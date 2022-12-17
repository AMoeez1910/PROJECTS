#include "raylib.h"
#include <string.h>
#include <ctype.h>
#define screenwidth 1000
#define screenheight 600
#define MAX_INPUT_CHARS 8
struct BALL
{
    float X,Y;
    float SpeedX,SpeedY,Speedtemp;
    float Radius;
};
int main()
{
InitWindow(screenwidth,screenheight,"AIR HOCKEY");
InitAudioDevice();
SetTargetFPS(60);
GAME:
Sound pong=LoadSound("pong.wav");
Sound Goal=LoadSound("si.ogg");
Music ucl=LoadMusicStream("ucl.mp3");
PlayMusicStream(ucl);
struct BALL Ball;

float dia=40.0f;
float offset=45.0f;
float posX=offset,posY=screenheight/2;
float posX1=screenwidth-offset,posY1=screenheight/2;
float PaddleSpeed=300;
float PaddleSpeed_BOOSTED=500;
Ball.X=screenwidth/2;
Ball.Y=screenheight/2;
Ball.Radius=20;
Ball.SpeedX=300;
Ball.SpeedY=300;
Ball.Speedtemp=250;
int PointsP1=0;
int PointsP2=0;
Rectangle s1={
    0,
    0,
    screenwidth,
    screenheight
};
Vector2 start={
    screenwidth/2,
    0
};
Vector2 end={
    screenwidth/2,
    screenheight,
};
//MAIN MENU
while (!WindowShouldClose())
{
    UpdateMusicStream(ucl);
BeginDrawing();
    ClearBackground(BLACK);
    //CENTRAL POSITION
    int textwidth=MeasureText("WELCOME TO AIR HOCKEY",60);
    int textwidth1=MeasureText("MAIN MENU",50);
    // int textwidth2=MeasureText("PRESS SPACEBAR TO CONTINUEAS MULTIPLAYER...",40);
    DrawText("MAIN MENU",screenwidth/2-textwidth1/2,10,50,RED);
    DrawText("WELCOME TO AIR HOCKEY",screenwidth/2-textwidth/2,screenheight/2-200,60,RAYWHITE);
    DrawText(">PRESS M FOR MULTIPLAYER\n>PRESS S FOR SINGLE PLAYER AGAINST CPU (INDEVELOPMENT)\n\tRULES:\n>MAXIMUM POINTS IS 200.FIRST TO SCORE WINS\n>PLAYER 1=WASD AND LEFT SHIFT to accelerate\n>PLAYER 2=UPDOWNRIGHTLEFT AND RIGHT SHIFT to accelerate",screenwidth/2-textwidth/2,screenheight/2-100,20,WHITE);
    DrawText("PRESS SPACEBAR TO EXIT",screenwidth/2-textwidth/2+30,screenheight/2+100,40,RED);
    DrawText("FOR NEW GAME = N\nTO RESTART = R\nTO QUIT GAME = Q\nTO PAUSE = P (INDEVELOPMENT)",screenwidth/2-textwidth/2,screenheight/2+200,15,GREEN);
EndDrawing();
    char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    Rectangle textBox = { screenwidth/2.0f - 100, 180, 225, 50 };
    bool mouseOnText = false;

    int framesCounter = 0;

//PLAYER 1 NAME
if (IsKeyPressed(KEY_M))
{
while (!WindowShouldClose() && !IsKeyPressed(KEY_LEFT_SHIFT))    // Detect window close button or ESC key
    {
        UpdateMusicStream(ucl);
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        int i=0;
        while(name[i])
        {
            name[i]=toupper(name[i]);
            i++;
        }
        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("ENTER PLAYER 1", 240, 140, 20, GRAY);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

            DrawText("PRESS LEFT SHIFT KEY TO CONTINUE", 315, 250, 20, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                }
                else DrawText("LIMIT REACHED", 230, 300, 20, GRAY);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    char name1[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int count = 0;

    Rectangle txtbox = { screenwidth/2.0f - 100, 180, 225, 50 };
    bool mouseontxt = false;

    int frameCount = 0;

//PLAYER 2 NAME

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ENTER) )    // Detect window close button or ESC key
    {
        UpdateMusicStream(ucl);
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), txtbox)) mouseontxt = true;
        else mouseontxt = false;

        if (mouseontxt)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (count < MAX_INPUT_CHARS))
                {
                    name1[count] = (char)key;
                    name1[count+1] = '\0'; // Add null terminator at the end of the string.
                    count++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                count--;
                if (count < 0) count = 0;
                name1[count] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        int i=0;
        while(name1[i])
        {
            name1[i]=toupper(name1[i]);
            i++;
        }
        if (mouseontxt) frameCount++;
        else frameCount = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("ENTER PLAYER 2", 240, 140, 20, GRAY);

            DrawRectangleRec(txtbox, LIGHTGRAY);
            if (mouseontxt) DrawRectangleLines((int)txtbox.x, (int)txtbox.y, (int)txtbox.width, (int)txtbox.height, RED);
            else DrawRectangleLines((int)txtbox.x, (int)txtbox.y, (int)txtbox.width, (int)txtbox.height, DARKGRAY);

            DrawText(name1, (int)txtbox.x + 5, (int)txtbox.y + 8, 40, MAROON);

            DrawText("PRESS ENTER TO CONTINUE", 315, 250, 20, DARKGRAY);

            if (mouseontxt)
            {
                if (count < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((frameCount/20)%2) == 0) DrawText("_", (int)txtbox.x + 8 + MeasureText(name1, 40), (int)txtbox.y + 12, 40, MAROON);
                }
                else DrawText("LIMIT REACHED", 230, 300, 20, GRAY);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //>>>>>>>GAME<<<<<<<<<<

if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_N) || IsKeyPressed(KEY_R))
{
while (!WindowShouldClose())
{
    //NEW GAME
    StopMusicStream(ucl);
        if (IsKeyPressed(KEY_Q))
        {
            goto Exit;
        }
        
        if (IsKeyPressed(KEY_N))
        {
            posX=offset;
            posY=screenheight/2;
            posX1=screenwidth-offset;
            posY1=screenheight/2;
            Ball.X=screenwidth/2;
            Ball.Y=screenheight/2;
            Ball.Radius=20;
            Ball.SpeedX=300;
            Ball.SpeedY=300;
            Ball.Speedtemp=250;
            PointsP1=0;
            PointsP2=0;
            goto GAME;
        }
    //RESTART
        if (IsKeyPressed(KEY_R))
        {
            posX=offset;
            posY=screenheight/2;
            posX1=screenwidth-offset;
            posY1=screenheight/2;
            Ball.X=screenwidth/2;
            Ball.Y=screenheight/2;
            Ball.Radius=20;
            Ball.SpeedX=300;
            Ball.SpeedY=300;
            Ball.Speedtemp=250;
            PointsP1=0;
            PointsP2=0;
        }
    if(PointsP1<200 && PointsP2<200)
    {
    BeginDrawing();                                 
        ClearBackground(BLACK);
//CHANGE SPEED ASWELL NOT CONST
        Ball.X+=Ball.SpeedX*GetFrameTime();
        Ball.Y+=Ball.SpeedY*GetFrameTime();

     if (Ball.Y>150+Ball.Radius && Ball.Y<450-Ball.Radius)
     {
         if ((Ball.X<0+Ball.Radius && Ball.X>0) || (Ball.X>1000-Ball.Radius && Ball.X<1000))
         {
             Ball.SpeedX=Ball.SpeedX;
             PlaySound(Goal);
         }
            
     }
     else 
         {
             if ((Ball.Y>600-Ball.Radius && Ball.Y<590)|| (Ball.Y<Ball.Radius && Ball.Y>10))
             {
                if(Ball.Y>600-Ball.Radius)
                    Ball.Y=600-Ball.Radius;
                else if (Ball.Y<Ball.Radius)
                    Ball.Y=Ball.Radius;

                 Ball.SpeedY=-Ball.SpeedY;
                 PlaySound(pong);
             }

             if ((Ball.X>1000-Ball.Radius && Ball.X<=990)  || (Ball.X<Ball.Radius && Ball.X>=10))
             {
                if (Ball.X>1000-Ball.Radius && Ball.X<1000)
                    Ball.X=1000-Ball.Radius;
                else if (Ball.X<Ball.Radius && Ball.X>0)
                    Ball.X=Ball.Radius;    
                 Ball.SpeedX=-Ball.SpeedX;
                 PlaySound(pong);
             }
         }
        
        if (IsKeyDown(KEY_D))
        {
            if(IsKeyDown(KEY_LEFT_SHIFT))
            posX+=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posX+=GetFrameTime()*PaddleSpeed;

            if (posX>screenwidth/2-offset)
            {
                posX=screenwidth/2-offset;
            }
        }
        if (IsKeyDown(KEY_A))
        {
            if(IsKeyDown(KEY_LEFT_SHIFT))
            posX-=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posX-=GetFrameTime()*PaddleSpeed;
            if (posX<offset)
            {
                posX=offset;
            }
        }
        if (IsKeyDown(KEY_S))
        {
            if(IsKeyDown(KEY_LEFT_SHIFT))
            posY+=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posY+=GetFrameTime()*PaddleSpeed;
            if (posY>screenheight-offset)
            {
                posY=screenheight-offset;
            }
        }
        if (IsKeyDown(KEY_W))
        {
            
            if(IsKeyDown(KEY_LEFT_SHIFT))
            posY-=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posY-=GetFrameTime()*PaddleSpeed;
            if (posY<offset)
            {
                posY=offset;
            }
        }

//PLAYER 2
    if (IsKeyDown(KEY_LEFT))
    {
         if(IsKeyDown(KEY_RIGHT_SHIFT))
            posX1-=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posX1-=GetFrameTime()*PaddleSpeed;
            if (posX1<screenwidth/2+offset)
            {
                posX1=screenwidth/2+offset;
            }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
         if(IsKeyDown(KEY_RIGHT_SHIFT))
            posX1+=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posX1+=GetFrameTime()*PaddleSpeed;
            if (posX1>screenwidth-offset)
            {
                posX1=screenwidth-offset;
            }
    }
    if (IsKeyDown(KEY_UP))
        {
            if(IsKeyDown(KEY_RIGHT_SHIFT))
            posY1-=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posY1-=GetFrameTime()*PaddleSpeed;
                if (posY1<offset)
                {
                    posY1=offset;
                }
        }
    if (IsKeyDown(KEY_DOWN))
        {
            if(IsKeyDown(KEY_RIGHT_SHIFT))
            posY1+=GetFrameTime()*PaddleSpeed_BOOSTED;
            else
            posY1+=GetFrameTime()*PaddleSpeed;
                if (posY1>screenheight-offset)
                {
                    posY1=screenheight-offset;
                }
        }
    Vector2 puck={
    Ball.X,
    Ball.Y
    };
    Vector2 paddle1={
        posX,
        posY
    };
    Vector2 paddle2={
        posX1,
        posY1
    };
    if (CheckCollisionCircles(puck,Ball.Radius,paddle1,dia))
    {
         if(Ball.SpeedX>0)
            Ball.SpeedX=Ball.SpeedX*1.005;
         if(Ball.SpeedX<0)
        Ball.SpeedX=-Ball.SpeedX;
        PlaySound(pong);

    }
    
    if (CheckCollisionCircles(puck,Ball.Radius,paddle2,dia))
    {
        if(Ball.SpeedX<0)
            Ball.SpeedX=-Ball.SpeedX*1.005;
        if(Ball.SpeedX>0)
        Ball.SpeedX=-Ball.SpeedX;
        PlaySound(pong);
        
    }

     if (Ball.Y>150+Ball.Radius && Ball.Y<450-Ball.Radius && Ball.X>1000-Ball.Radius)
    {
        PointsP1+=50;
        Ball.X=screenwidth/2;
        Ball.Y=screenheight/2;
        Ball.Radius=20;
        Ball.SpeedX=300;
        Ball.SpeedY=300;
        Ball.Speedtemp=250;
    }

    
    if (Ball.Y>150+Ball.Radius && Ball.Y<450-Ball.Radius && Ball.X<0+Ball.Radius)
    {
        PointsP2+=50;
        Ball.X=screenwidth/2;
        Ball.Y=screenheight/2;
        Ball.Radius=20;
        Ball.SpeedX=300;
        Ball.SpeedY=300;
        Ball.Speedtemp=250;
    }

        DrawText(TextFormat("%d",PointsP1),screenwidth/2-280,90,40,BLUE);
        DrawText(TextFormat("%d",PointsP2),screenwidth/2+80,90,40,RED);
        DrawText(name,screenwidth/2-280,45,40,BLUE);
        DrawText(name1,screenwidth/2+80,45,40,RED);
        DrawRectangleLinesEx(s1,5,YELLOW);
        // DrawCircleLines(screenwidth/2,screenheight/2,80,WHITE);
        DrawCircle(screenwidth/2,screenheight/2,80,WHITE);
        DrawCircle(screenwidth/2,screenheight/2,70,BLACK);
        DrawRectangle(0,screenheight/2-150,10,300,BLACK);
        DrawRectangle(screenwidth-10,screenheight/2-150,10,300,BLACK);
        DrawCircle(screenwidth/2,screenheight/2,10,WHITE);
        DrawLineEx(start,end,10,WHITE);
       
        DrawCircle(Ball.X,Ball.Y,Ball.Radius,ORANGE);
        //player 1 paddle 1
        DrawCircleGradient(posX,posY,dia,BLUE,RED);
        //player 2 paddle 2
        DrawCircleGradient(posX1,posY1,dia,BLUE,RED);
    }
        if (PointsP1==200)
        {
            ClearBackground(BLACK);
            DrawRectangleLinesEx(s1,5,YELLOW);
            DrawCircle(screenwidth/2,screenheight/2,80,WHITE);
            DrawCircle(screenwidth/2,screenheight/2,70,BLACK);
            DrawRectangle(0,screenheight/2-150,10,300,BLACK);
            DrawRectangle(screenwidth-10,screenheight/2-150,10,300,BLACK);
            DrawCircle(screenwidth/2,screenheight/2,10,WHITE);
            DrawLineEx(start,end,10,WHITE);
            DrawCircle(Ball.X,Ball.Y,Ball.Radius,ORANGE);
            DrawCircleGradient(posX,posY,dia,BLUE,RED);
            DrawCircleGradient(posX1,posY1,dia,BLUE,RED);
            DrawText(TextFormat("%s WINS \n%d",name,PointsP1),screenwidth/2-360,45,40,BLUE);
        }
        else if (PointsP2==200)
        {
            ClearBackground(BLACK);
            DrawRectangleLinesEx(s1,5,YELLOW);
            DrawCircle(screenwidth/2,screenheight/2,80,WHITE);
            DrawCircle(screenwidth/2,screenheight/2,70,BLACK);
            DrawRectangle(0,screenheight/2-150,10,300,BLACK);
            DrawRectangle(screenwidth-10,screenheight/2-150,10,300,BLACK);
            DrawCircle(screenwidth/2,screenheight/2,10,WHITE);
            DrawLineEx(start,end,10,WHITE);
            DrawCircle(Ball.X,Ball.Y,Ball.Radius,ORANGE);
            DrawCircleGradient(posX,posY,dia,BLUE,RED);
            DrawCircleGradient(posX1,posY1,dia,BLUE,RED);
            DrawText(TextFormat("%s WINS \n%d",name1,PointsP1),screenwidth/2+80,45,40,RED);
        }    
        
        
    EndDrawing();
}
}
}
else if (IsKeyPressed(KEY_SPACE))
goto Exit;
} 
Exit:
CloseAudioDevice();
CloseWindow();
return 0;
}