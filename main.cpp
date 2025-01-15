#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color green = {173,204,96,255};
Color darkgreen = {43,51,24,255};

int cellcount = 25;
int cellsize = 30;
int score = 0;

class Food
{
public:
    Vector2 position;
    Food()
    {
        position = RandomPosi();
    }

    void Draw()
    {
        Rectangle frec = Rectangle{position.x*cellsize, position.y*cellsize, (float)cellsize, (float)cellsize};
        DrawRectangleRounded(frec, 0.5, 6, RED);
    }
            
    Vector2 RandomPosi()
    {
        float x = GetRandomValue(0, cellcount-1);
        float y = GetRandomValue(0, cellcount-1);
        return Vector2{x,y};
    }
};

class Snake
{
public:


    deque<Vector2> body = {Vector2{3,3}, Vector2{4,3}, Vector2{5,3}};

    Vector2 direction = {1,0};

    int len = 3;

    void Eat()
    {
        body.push_back(body[len-1]);
        int x = body[len-1].x;
        int y = body[len-1].y;
        Rectangle unit = Rectangle{(float)x*cellsize, (float)y*cellsize, (float)cellsize, (float)cellsize};
        DrawRectangleRounded(unit, 0.5, 6, darkgreen);
    }

    void Draw()
    {
        for(int i=0; i < body.size(); i++)
        {
            int x = body[i].x;
            int y = body[i].y;
            Rectangle unit = Rectangle{(float)x*cellsize, (float)y*cellsize, (float)cellsize, (float)cellsize};
            DrawRectangleRounded(unit, 0.5, 6, darkgreen);
        }
    }

    void Move()
    {  
        body.pop_back();
        body.push_front(body[0]+direction);
    }

};

int main()
{
    SetRandomSeed(time(nullptr));

    Food food;
    Snake snake;

    cout << "Initializing!!" << endl;
    InitWindow(cellsize*cellcount, cellsize*cellcount, "Snake Rand");
    SetTargetFPS(10);
    
    while(!WindowShouldClose())
    {

		Rectangle head = {snake.body[0].x * cellsize, snake.body[0].y * cellsize, (float)cellsize, (float)cellsize};
		Rectangle f = {food.position.x * cellsize, food.position.y * cellsize,(float)cellsize, (float)cellsize};
		bool col = CheckCollisionRecs(f , head);
        // bool colbody = false;

        // for(int i=2;i<snake.len;i++)
        // {
        //     Rectangle rec = {snake.body[i].x * cellsize, snake.body[i].y * cellsize, (float)cellsize, (float)cellsize};
        //     if(CheckCollisionRecs(head,rec))
        //     {
        //         colbody = true;
        //     }
        // }

        BeginDrawing();

        ClearBackground(green);

        if (snake.body[0].x >= 25 || snake.body[0].y >= 25 || snake.body[0].x < 0 || snake.body[0].y < 0)
        {
            DrawText("OVER!!",10,10,40,BLACK);
        }
        else
        {
            if (col)
            {
                food.position = food.RandomPosi();
                snake.Eat();
                snake.len ++;
                score++;
            }
            food.Draw();
            snake.Draw();
            DrawText(TextFormat("%i",score), 5, 5, 25, BLACK);

            if(IsKeyDown(KEY_UP) && snake.direction.y != 1) snake.direction = {0,-1};

            if(IsKeyDown(KEY_DOWN) && snake.direction.y != -1) snake.direction = {0,1};
            
            if(IsKeyDown(KEY_LEFT) && snake.direction.x != 1) snake.direction = {-1,0};
            
            if(IsKeyDown(KEY_RIGHT) && snake.direction.x != -1) snake.direction = {1,0};
            
            snake.Move();
            
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
