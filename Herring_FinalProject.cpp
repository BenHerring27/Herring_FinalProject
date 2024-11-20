#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
using namespace sfp;

const float KB_SPEED = 0.2;

void LoadTex(Texture& tex, string filename) {
    if (!tex.loadFromFile(filename)) {
        cout << "Could not load " << filename << endl;
    }
}

void MoveCrossbow(PhysicsRectangle paddle, int elapsedMS) {
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        Vector2f newPos(paddle.getCenter());
        newPos.y = newPos.y + (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        Vector2f newPos(paddle.getCenter());
        newPos.y = newPos.y - (KB_SPEED * elapsedMS);
        paddle.setCenter(newPos);
    }
}

Vector2f GetTextSize(Text text) {
    FloatRect r = text.getGlobalBounds();
    return Vector2f(r.width, r.height);
}



int main()
{
    RenderWindow window(VideoMode(800, 600), "Balloon Buster");
    World world(Vector2f(0, 0));
    int score1(0);
    int score2(0);



    PhysicsRectangle paddle1;
    paddle1.setSize(Vector2f(10, 30));
    paddle1.setCenter(Vector2f(30, 300));
    world.AddPhysicsBody(paddle1);

    PhysicsCircle ball;
    ball.setSize(Vector2f(50, 50));
    ball.setCenter(Vector2f(400, 300));
    world.AddPhysicsBody(ball);

    PhysicsRectangle top;
    top.setSize(Vector2f(800, 10));
    top.setCenter(Vector2f(400, 5));
    top.setStatic(true);
    world.AddPhysicsBody(top);

    PhysicsRectangle left;
    left.setSize(Vector2f(10, 600));
    left.setCenter(Vector2f(5, 300));
    left.setStatic(true);
    world.AddPhysicsBody(left);

    PhysicsRectangle right;
    right.setSize(Vector2f(10, 600));
    right.setCenter(Vector2f(795, 300));
    right.setStatic(true);
    world.AddPhysicsBody(right);
    right.onCollision = [&ball](PhysicsBodyCollisionResult result) {
        
    };


    PhysicsShapeList<PhysicsSprite> ducks;





    Font fnt;
    if (!fnt.loadFromFile("arial.ttf")) {
        cout << "Could not load font." << endl;
        exit(3);
    }
    Clock clock;
    Time lastTime(clock.getElapsedTime());
    Time currentTime(lastTime);
    Time lastDuckTime(clock.getElapsedTime());
    while (score1 == 0) {
        currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        long deltaMS = deltaTime.asMilliseconds();
        if (deltaMS > 9) {

            lastTime = currentTime;
            world.UpdatePhysics(deltaMS);
            MoveCrossbow(paddle1, deltaMS);

            

            Time duckDelta = currentTime - lastDuckTime;
            long duckMS = duckDelta.asMilliseconds();
            //if (duckMS > 2000) {
                //lastDuckTime = currentTime;
                //PhysicsSprite& duck = ducks.Create();
                //duck.setTexture(duckTex);
                //Vector2f sz = duck.getSize();
                //duck.setCenter(Vector2f(50, 20 + (sz.y / 2)));
                //duck.setVelocity(Vector2f(0.25, 0));
                //world.AddPhysicsBody(duck);
                //duck.onCollision =
                    //[&drawingArrow, &world, &arrow, &duck, &ducks, &score1, &right]
                //(PhysicsBodyCollisionResult result) {
                    //if (result.object2 == arrow) {
                        //drawingArrow = false;
                        //world.RemovePhysicsBody(arrow);
                        //world.RemovePhysicsBody(duck);
                        //ducks.QueueRemove(duck);
                        //score1 += 10;
                    //}
                    //if (result.object2 == right) {
                        //world.RemovePhysicsBody(duck);
                        //ducks.QueueRemove(duck);
                    //}
                //};
        }
        ducks.DoRemovals();



        window.draw(paddle1);
        for (PhysicsSprite& duck : ducks) {
            window.draw(duck);
        }
        Text scoreText;
        scoreText.setString(to_string(score1));
        scoreText.setFont(fnt);
        window.draw(scoreText);
        //world.VisualizeAllBounds(window);

        window.display();

    }
}

   

