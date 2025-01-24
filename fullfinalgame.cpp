#include "raylib.h"
#include <string>

const int screenWidth = 800;
const int screenHeight = 600;
const float Player_speed = 7.0f;
const float gravity = 0.5f;
const float jumpStrength = -10.0f;
const float bulletRadius = 5.0f;
const float bulletspeed = 10.0f;
const float birdSpeed = 7.0f;
const int numCollectibles_set1 = 14;
const int Platform_set1 = 20;
const int numCollectibles_set2 = 30;
const int Platform_set2 = 31;
const int maxBullets = 10;
const int birdSize = 64;
const int num_bird1 = 14;
const int num_bird2 = 29;


class Player;
class Platform;
class Enemies;
class Collectible;
class Bullet;

// Collectible 
class Collectible
{
public:
    Rectangle rect;
    bool collected;

    Collectible() : collected(false) {} 

    Collectible(Rectangle r) : rect(r), collected(false) {} 

    void draw() 
    {
        if (!collected) 
        {
            DrawRectangleRec(rect, GOLD);
        }
    }
};

// Bullet 
class Bullet 
{
public:
    Vector2 position;
    bool fire;

    Bullet() : fire(false) {} 

    void update(float bulletspeed)
    {
        if (fire)
        {
            position.x += bulletspeed;
        }
    }

    void draw() 
    {
        if (fire) 
        {
            DrawCircleV(position, bulletRadius, YELLOW);
        }
    }
};

// Platform 
class Platform 
{
    
public:
    Rectangle rect;

    Platform() {} 

    Platform(Rectangle r) : rect(r) {} 

    void draw(Texture2D groundTexture, Texture2D largeTexture, Texture2D floatingTexture, Texture2D jumpTexture, Texture2D groundTexture1, Texture2D largeTexture1, Texture2D floatingTexture1, Texture2D jumpTexture2, int level) {

        if (level == 1) 
        {
            if (rect.width > 500) {
                DrawTexture(groundTexture, (int)rect.x, (int)rect.y, WHITE);
            }
            else if (rect.width >= 300) {
                DrawTexture(largeTexture, (int)rect.x, (int)rect.y, WHITE);
            }
            else if (rect.width >= 100) {
                DrawTexture(floatingTexture, (int)rect.x, (int)rect.y, WHITE);
            }
            else if (rect.width >= 30) {
                DrawTexture(jumpTexture, (int)rect.x, (int)rect.y, WHITE);
            }
            else {
                DrawTexture(largeTexture, (int)rect.x, (int)rect.y, WHITE);
            }
        }
        if (level == 2) 
        {
            if (rect.width > 500) {
                DrawTexture(groundTexture1, (int)rect.x, (int)rect.y, WHITE);
            }
            else if (rect.width >= 280) {
                DrawTexture(largeTexture1, (int)rect.x, (int)rect.y, WHITE);
            }
            else if (rect.width >= 100) {
                DrawTexture(floatingTexture1, (int)rect.x, (int)rect.y, WHITE);
            }
            else if (rect.width >= 25) {
                DrawTexture(jumpTexture2, (int)rect.x, (int)rect.y, WHITE);
            }
            else {
                DrawTexture(largeTexture1, (int)rect.x, (int)rect.y, WHITE);
            }
        }
    }
};

// Player
class Player 
{
public:
    Rectangle rect;
    Vector2 velocity;
    bool onGround;
    Rectangle player_run;

    Player() : rect({ 50, 450, 64, 64 }), velocity({ 0, 0 }), onGround(false), player_run({ 0, 2368 - 512, 64, 64 }) {}

    void run_right(float Player_speed, float& scrollingX, Texture2D background) 
    {
        if (IsKeyDown(KEY_RIGHT) && onGround) 
        {
            player_run.y = 2368;
            player_run.x += 64;
            if (player_run.x == 64 * 7) 
            {
                player_run.x = 0;
            }
            rect.x += Player_speed;
            scrollingX -= 6.0f;
        }
    }

    void jump_Rrun(float Player_speed, float& scrollingX, Texture2D background) 
    {
        if (IsKeyDown(KEY_RIGHT) && !onGround) 
        {
            rect.x += Player_speed;
            scrollingX -= 6.0f;
        }
    }

    void run_left(float Player_speed, float& scrollingX, Texture2D background) 
    {
        if (IsKeyDown(KEY_LEFT)) 
        {
            player_run.y = 2304 - 64;
            rect.x -= Player_speed;
            player_run.x += 64;
            if (player_run.x == 448) {
                player_run.x = 0;
            }
        }
    }

    void jump(float jumpStrength, Sound jumpSound) 
    {
        if (IsKeyPressed(KEY_SPACE) && onGround) 
        {
            velocity.y = jumpStrength;
            onGround = false;
            PlaySound(jumpSound);
        }
    }

    void player_static() 
    {
        if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_SPACE)) 
        {
            player_run.x = 0;
            player_run.y = 2368 - 512;
        }
    }

    void player_gravity(float gravity) 
    {
        velocity.y += gravity;
        rect.y += velocity.y;
    }
    void collect_coins(Collectible collectibles[], int numCollectibles, int& score, Sound collectSound) 
    {
        for (int i = 0; i < numCollectibles; i++) 
        {
            if (!collectibles[i].collected && CheckCollisionRecs(rect, collectibles[i].rect)) 
            {
                collectibles[i].collected = true;
                score += 10;
                PlaySound(collectSound);
            }
        }
    }

    void live(int& lives) 
    {
        if (rect.y > 700) 
        {
            lives--;
            rect.x = 50;
            rect.y = 500;
        }
    }

    void firing(Bullet bullets[], Sound bulletSound, int maxBullets) 
    {
        if (IsKeyPressed(KEY_Z)) 
        {
            for (int i = 0; i < maxBullets; i++) 
            {
                if (!bullets[i].fire) 
                {
                    bullets[i].fire = true;
                    bullets[i].position.x = rect.x + 64;
                    bullets[i].position.y = rect.y + 32;
                    PlaySound(bulletSound);
                    break;
                }
            }
        }
    }

    void draw_lives(Texture2D heartTexture, int& x1, int& y1, int lives) 
    {
        for (int j = 0; j < lives; j++) 
        {
            DrawTexture(heartTexture, x1, y1, WHITE);
            x1 += 60 + 10;
        }
    }

    void draw(Texture2D playerTexture) 
    {
        DrawTextureRec(playerTexture, player_run, (Vector2){ rect.x, rect.y }, WHITE);
    }
};

// Enemies 
class Enemies 
{
public:
    Rectangle rect;
    bool isAlive;
    Rectangle enemey_run;
    int b;


    Enemies() : isAlive(true), enemey_run({ 0, 0, 64, 64 }), b(0) {}

    Enemies(Rectangle r) : rect(r), isAlive(true), enemey_run({ 0, 0, 64, 64 }), b(0) {}

    void update(Player& player) 
    {
        if (isAlive) 
        {
            if (player.rect.x - rect.x < 400 && player.rect.x - rect.x > -400) {
                if (b <= 5) {
                    enemey_run.x += 64;
                    enemey_run.y = 0;
                    b++;
                }
                if (enemey_run.x >= 256) {
                    enemey_run.x = 0;
                }

                if (b > 5) {
                    enemey_run.y = 64;
                    enemey_run.x += 64;
                    b++;
                    if (b == 10) {
                        b = 0;
                    }
                }
                rect.x -= birdSpeed;
            }
        }
    }

    void draw(Texture2D enemey1Texture) 
    {
        if (isAlive) 
        {
            DrawTextureRec(enemey1Texture, enemey_run, (Vector2){ rect.x, rect.y }, WHITE);
        }
    }
};

//Game 
class GameManager 
{
public:
    Rectangle game;
    Rectangle main;
    Rectangle restart;
    Rectangle exit;
    int gamemode;
    int lives;
    int score;
    float scrollingX;
    bool gameWon;

    Sound jumpSound;
    Sound collectSound;
    Sound bulletSound;
    Sound losingSound;
    Music mainSound;
    Music gameSound;
    Music winSound;

    Texture2D floatingTexture;
    Texture2D floatingTexture1;
    Texture2D jumpTexture;
    Texture2D jumpTexture2;
    Texture2D playerTexture;
    Texture2D groundTexture;
    Texture2D groundTexture1;
    Texture2D heartTexture;
    Texture2D enemey1Texture;
    Texture2D background;
    Texture2D background1;
    Texture2D mainmenu;
    Texture2D largeTexture;
    Texture2D largeTexture1;
    Texture2D loosing;
    Font font;

    Player player;
    Bullet bullets[maxBullets];
    Platform platform_a[Platform_set1];
    Platform platform_b[Platform_set2];
    Collectible collectibles1[numCollectibles_set1];
    Collectible collectibles2[numCollectibles_set2];
    Enemies birds_a[num_bird1];
    Enemies birds_b[num_bird2];

    GameManager() :
        game({ (screenWidth / 2) - 100, (screenHeight / 2) - 50, 200, 100 }),
        main({ (screenWidth / 2) - 100, (screenHeight / 2) - 50, 200, 100 }),
        restart({ (screenWidth / 2) - 100, (screenHeight / 2) - 50 + 110, 200, 100 }),
        exit({ (screenWidth / 2) - 100, (screenHeight / 2) - 50 + 220, 200, 100 }),
        gamemode(0),
        lives(3),
        score(0),
        scrollingX(0.0f),
        gameWon(false) {


        jumpSound = LoadSound("Jump_sound.mp3");
        collectSound = LoadSound("collect_sound.mp3");
        bulletSound = LoadSound("bullet_sound.mp3");
        losingSound = LoadSound("losing sound.mp3");
        mainSound = LoadMusicStream("mains m s.mp3");
        gameSound = LoadMusicStream("game.mp3");
        winSound = LoadMusicStream("gamewin.mp3");

        floatingTexture = LoadTexture("floating.png");
        floatingTexture1 = LoadTexture("floating1.png");
        jumpTexture = LoadTexture("jump1.png");
        jumpTexture2 = LoadTexture("jump2.png");
        playerTexture = LoadTexture("./player_sprite.png");
        groundTexture = LoadTexture("./ground platform12.png");
        groundTexture1 = LoadTexture("./ground platform11.png");
        heartTexture = LoadTexture("./heart11.png");
        enemey1Texture = LoadTexture("./bird.png");
        background = LoadTexture("background.png");
        background1 = LoadTexture("background1.png");
        mainmenu = LoadTexture("Main menu.png");
        largeTexture = LoadTexture("large.png");
        largeTexture1 = LoadTexture("large1.png");
        loosing = LoadTexture("loosing.png");
       // font = LoadFont("resources/Bangers-Regular.ttf");

        //bullets
        for (int i = 0; i < maxBullets; i++) 
        {
            bullets[i].fire = false;
        }

        //platform_a
        platform_a[0] = Platform({ 0, 550, 1200, 2 });
        platform_a[1] = Platform({ 1300, 450, 200, 2 });
        platform_a[2] = Platform({ 1600, 400, 200, 2 });
        platform_a[3] = Platform({ 1900, 350, 200, 2 });
        platform_a[4] = Platform({ 2200, 550, 300, 2 });
        platform_a[5] = Platform({ 2600, 450, 30, 2 });
        platform_a[6] = Platform({ 2650, 300, 30, 2 });
        platform_a[7] = Platform({ 2700, 200, 30, 2 });
        platform_a[8] = Platform({ 3000, 500, 200, 2 });
        platform_a[9] = Platform({ 3300, 450, 200, 2 });
        platform_a[10] = Platform({ 3600, 400, 200, 2 });
        platform_a[11] = Platform({ 3900, 550, 1200, 2 });
        platform_a[12] = Platform({ 5200, 450, 300, 2 });
        platform_a[13] = Platform({ 5600, 350, 30, 2 });
        platform_a[14] = Platform({ 5650, 250, 30, 2 });
        platform_a[15] = Platform({ 5700, 150, 30, 2 });
        platform_a[16] = Platform({ 6000, 400, 200, 2 });
        platform_a[17] = Platform({ 6300, 350, 200, 2 });
        platform_a[18] = Platform({ 6600, 300, 200, 2 });
        platform_a[19] = Platform({ 6900, 250, 300, 2 });

        //platform_b
        platform_b[0] = Platform({ 0, 550, 1200, 2 });
        platform_b[1] = Platform({ 1300, 430, 185, 2 });
        platform_b[2] = Platform({ 1600, 380, 185, 2 });
        platform_b[3] = Platform({ 1900, 330, 185, 2 });
        platform_b[4] = Platform({ 2200, 280, 185, 2 });
        platform_b[5] = Platform({ 2550, 430, 25, 2 });
        platform_b[6] = Platform({ 2650, 330, 25, 2});
        platform_b[7] = Platform({ 2750, 230, 25, 2 });
        platform_b[8] = Platform({ 3000, 480, 185, 2 });
        platform_b[9] = Platform({ 3200, 430, 185, 2 });
        platform_b[10] = Platform({ 3400, 380, 185, 2 });
        platform_b[11] = Platform({ 3600, 530, 285, 2 });
        platform_b[12] = Platform({ 3900, 430, 1200, 2 });
        platform_b[13] = Platform({ 5000, 380, 285, 2 });
        platform_b[14] = Platform({ 5300, 330, 25, 2 });
        platform_b[15] = Platform({ 5400, 230, 25, 2 });
        platform_b[16] = Platform({ 5600, 180, 25, 2 });
        platform_b[17] = Platform({ 5800, 430, 185, 2 });
        platform_b[18] = Platform({ 6100, 330, 185, 2 });
        platform_b[19] = Platform({ 6300, 280, 185, 2 });
        platform_b[20] = Platform({ 6600, 230, 285, 2 });
        platform_b[21] = Platform({ 6800, 230, 285, 2 });
        platform_b[22] = Platform({ 7000, 230, 285, 2 });
        platform_b[23] = Platform({ 7300, 180, 1200, 2 });

        // collectibles1
        collectibles1[0] = Collectible({ 1350, 420, 20, 20 });
        collectibles1[1] = Collectible({ 1650, 370, 20, 20 });
        collectibles1[2] = Collectible({ 1950, 320, 20, 20 });
        collectibles1[3] = Collectible({ 2650, 270, 20, 20 });
        collectibles1[4] = Collectible({ 2700, 170, 20, 20 });
        collectibles1[5] = Collectible({ 3050, 470, 20, 20 });
        collectibles1[6] = Collectible({ 3350, 420, 20, 20 });
        collectibles1[7] = Collectible({ 3650, 370, 20, 20 });
        collectibles1[8] = Collectible({ 5250, 420, 20, 20 });
        collectibles1[9] = Collectible({ 5650, 220, 20, 20 });
        collectibles1[10] = Collectible({ 6000, 370, 20, 20 });
        collectibles1[11] = Collectible({ 6350, 320, 20, 20 });
        collectibles1[12] = Collectible({ 6650, 270, 20, 20 });
        collectibles1[13] = Collectible({ 6950, 220, 20, 20 });

        // collectibles2
        collectibles2[0] = Collectible({ 1350, 420, 20, 20 });
        collectibles2[1] = Collectible({ 1650, 370, 20, 20 });
        collectibles2[2] = Collectible({ 1850, 320, 20, 20 });
        collectibles2[3] = Collectible({ 2200, 270, 20, 20 });
        collectibles2[4] = Collectible({ 2500, 400, 20, 20 });
        collectibles2[5] = Collectible({ 2650, 300, 20, 20 });
        collectibles2[6] = Collectible({ 2750, 210, 20, 20 });
        collectibles2[7] = Collectible({ 3000, 470, 20, 20 });
        collectibles2[8] = Collectible({ 3200, 420, 20, 20 });
        collectibles2[9] = Collectible({ 3400, 370, 20, 20 });
        collectibles2[10] = Collectible({ 3600, 520, 20, 20 });
        collectibles2[11] = Collectible({ 3900, 420, 20, 20 });
        collectibles2[12] = Collectible({ 5000, 370, 20, 20 });
        collectibles2[13] = Collectible({ 5300, 225, 20, 20 });
        collectibles2[14] = Collectible({ 5400, 125, 20, 20 });
        collectibles2[15] = Collectible({ 5600, 75, 20, 20 });
        collectibles2[16] = Collectible({ 5800, 420, 20, 20 });
        collectibles2[17] = Collectible({ 6100, 320, 20, 20 });
        collectibles2[18] = Collectible({ 6300, 270, 20, 20 });
        collectibles2[19] = Collectible({ 6600, 220, 20, 20 });
        collectibles2[20] = Collectible({ 7000, 170, 20, 20 });

        // birds_a
        birds_a[0] = Enemies({ 1350, 356, birdSize, birdSize });
        birds_a[1] = Enemies({ 1650, 306, birdSize, birdSize });
        birds_a[2] = Enemies({ 1950, 256, birdSize, birdSize });
        birds_a[3] = Enemies({ 2250, 456, birdSize, birdSize });
        birds_a[4] = Enemies({ 3050, 406, birdSize, birdSize });
        birds_a[5] = Enemies({ 3350, 356, birdSize, birdSize });
        birds_a[6] = Enemies({ 3650, 306, birdSize, birdSize });
        birds_a[7] = Enemies({ 3950, 456, birdSize, birdSize });
        birds_a[8] = Enemies({ 5250, 356, birdSize, birdSize });
        birds_a[9] = Enemies({ 6050, 306, birdSize, birdSize });
        birds_a[10] = Enemies({ 6350, 256, birdSize, birdSize });
        birds_a[11] = Enemies({ 6650, 206, birdSize, birdSize });
        birds_a[12] = Enemies({ 6950, 156, birdSize, birdSize });

        // Initialize birds_b
        birds_b[0] = Enemies({ 1300, 460, 64, 64 });
        birds_b[1] = Enemies({ 1600, 410, 64, 64 });
        birds_b[2] = Enemies({ 1900, 360, 64, 64 });
        birds_b[3] = Enemies({ 2200, 290, 64, 64 });
        birds_b[4] = Enemies({ 2550, 460, 64, 64 });
        birds_b[5] = Enemies({ 2650, 360, 64, 64 });
        birds_b[6] = Enemies({ 2750, 260, 64, 64 });
        birds_b[7] = Enemies({ 3000, 510, 64, 64 });
        birds_b[8] = Enemies({ 3200, 460, 64, 64 });
        birds_b[9] = Enemies({ 3400, 410, 64, 64 });
        birds_b[10] = Enemies({ 3600, 560, 64, 64 });
        birds_b[11] = Enemies({ 3900, 460, 64, 64 });
        birds_b[12] = Enemies({ 5000, 410, 64, 64 });
        birds_b[13] = Enemies({ 5300, 235, 64, 64 });
        birds_b[14] = Enemies({ 5400, 135, 64, 64 });
        birds_b[15] = Enemies({ 5600, 85, 64, 64 });
        birds_b[16] = Enemies({ 5800, 460, 64, 64 });
        birds_b[17] = Enemies({ 6100, 360, 64, 64 });
        birds_b[18] = Enemies({ 6300, 310, 64, 64 });
        birds_b[19] = Enemies({ 6600, 260, 64, 64 });
        birds_b[20] = Enemies({ 7000, 210, 64, 64 });
    }

    ~GameManager()
    {
        UnloadSound(jumpSound);
        UnloadSound(collectSound);
        UnloadSound(bulletSound);
        UnloadSound(losingSound);
        UnloadMusicStream(mainSound);
        UnloadMusicStream(gameSound);
        UnloadMusicStream(winSound);
        UnloadTexture(floatingTexture);
        UnloadTexture(floatingTexture1);
        UnloadTexture(jumpTexture);
        UnloadTexture(jumpTexture2);
        UnloadTexture(playerTexture);
        UnloadTexture(groundTexture);
        UnloadTexture(groundTexture1);
        UnloadTexture(heartTexture);
        UnloadTexture(enemey1Texture);
        UnloadTexture(background);
        UnloadTexture(background1);
        UnloadTexture(mainmenu);
        UnloadTexture(largeTexture);
        UnloadTexture(largeTexture1);
        UnloadTexture(loosing);
        UnloadFont(font);
    }

    void update(Camera2D& camera) 
    {

        Vector2 mousePosition = GetMousePosition();

        if (gamemode == 0) 
        {
            PlayMusicStream(mainSound);
            if (CheckCollisionPointRec(mousePosition, game) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                gamemode = 1;
            }
            UpdateMusicStream(mainSound);
        }
        else if (gamemode == 1) 
        {
            PlayMusicStream(gameSound);

            if (!gameWon) 
            {
                for (int i = 0; i < maxBullets; i++) 
                {
                    bullets[i].update(bulletspeed);
                    if (bullets[i].position.x > player.rect.x + screenWidth) 
                    {
                        bullets[i].fire = false;
                    }
                }

                for (int i = 0; i < num_bird1; i++) 
                {
                    birds_a[i].update(player);
                }

                // Collision Detection
                for (int i = 0; i < num_bird1; i++) 
                {
                    if (birds_a[i].isAlive && CheckCollisionRecs(player.rect, birds_a[i].rect)) 
                    {

                        lives--;
                        player.rect.x = 0;
                    }

                    for (int j = 0; j < maxBullets; j++) 
                    {
                        if (bullets[j].fire && birds_a[i].isAlive && CheckCollisionCircleRec(bullets[j].position, bulletRadius, birds_a[i].rect)) 
                        {
                            birds_a[i].isAlive = false;
                            bullets[j].fire = false;
                            score += 50;
                        }
                    }
                }

                player.run_right(Player_speed, scrollingX, background);
                player.jump_Rrun(Player_speed, scrollingX, background);
                player.run_left(Player_speed, scrollingX, background);
                player.jump(jumpStrength, jumpSound);
                player.player_static();
                player.player_gravity(gravity);
                player.collect_coins(collectibles1, numCollectibles_set1, score, collectSound);
                player.live(lives);
                gameWon = true;
                for (int i = 0; i < numCollectibles_set1; i++) 
                {
                    if (!collectibles1[i].collected) 
                    {
                        gameWon = false;

                    }
                }

                player.firing(bullets, bulletSound, maxBullets);

                if (lives == 0) 
                {
                    gamemode = 3;
                    PlaySound(losingSound);
                }

                if (scrollingX <= -background.width) 
                {
                    scrollingX = 0.0f;
                }

                for (int i = 0; i < Platform_set1; i++) 
                {
                    if (CheckCollisionRecs(player.rect, platform_a[i].rect) && player.rect.y > 0) {
                        player.onGround = true;
                    }
                    if (CheckCollisionRecs(player.rect, platform_a[i].rect) &&
                        player.rect.y >= (platform_a[i].rect.y - player.rect.height)) 
                        {
                        player.rect.y = platform_a[i].rect.y - player.rect.height;
                        player.velocity.y = 0;
                        player.onGround = true;
                    }
                }

                camera.target = (Vector2){ player.rect.x + player.rect.width / 2 -( screenWidth/2),player.rect.y + player.rect.height / 2 -(screenHeight/2)};
            }
            else {
                if (IsKeyPressed(KEY_R)) {
                    gamemode = 4;
                    player = Player();
                    gameWon = false;
                }
            }
            UpdateMusicStream(gameSound);
        }

        else if (gamemode == 4) {
            PlayMusicStream(gameSound);

            if (!gameWon) {
                for (int i = 0; i < maxBullets; i++) {
                    bullets[i].update(bulletspeed);
                    if (bullets[i].position.x > player.rect.x + screenWidth) {
                        bullets[i].fire = false;
                    }
                }

                for (int i = 0; i < num_bird2; i++) {
                    birds_b[i].update(player);
                }

                // Collision Detection
                for (int i = 0; i < num_bird2; i++) {
                    if (birds_b[i].isAlive && CheckCollisionRecs(player.rect, birds_b[i].rect)) {

                        lives--;
                        player.rect.x = 0;
                    }

                    for (int j = 0; j < maxBullets; j++) {
                        if (bullets[j].fire && birds_b[i].isAlive && CheckCollisionCircleRec(bullets[j].position, bulletRadius, birds_b[i].rect)) {
                            birds_b[i].isAlive = false;
                            bullets[j].fire = false;
                            score += 50;
                        }
                    }
                }

                player.run_right(Player_speed, scrollingX, background1);
                player.jump_Rrun(Player_speed, scrollingX, background1);
                player.run_left(Player_speed, scrollingX, background1);
                player.jump(jumpStrength, jumpSound);
                player.player_static();
                player.player_gravity(gravity);
                player.collect_coins(collectibles2, numCollectibles_set2, score, collectSound);
                player.live(lives);
                gameWon = true;
                for (int i = 0; i < numCollectibles_set2; i++) {
                    if (!collectibles2[i].collected) {
                        gameWon = false;
                    }
                }

                player.firing(bullets, bulletSound, maxBullets);

                if (lives == 0) {
                    gamemode = 3;
                    PlaySound(losingSound);
                }

                if (scrollingX <= -background1.width) {
                    scrollingX = 0.0f;
                }

                for (int i = 0; i < Platform_set2; i++) {
                    if (CheckCollisionRecs(player.rect, platform_b[i].rect) && player.rect.y > 0) {
                        player.onGround = true;
                    }
                    if (CheckCollisionRecs(player.rect, platform_b[i].rect) &&
                        player.rect.y >= (platform_b[i].rect.y - player.rect.height)) {
                        player.rect.y = platform_b[i].rect.y - player.rect.height;
                        player.velocity.y = 0;
                        player.onGround = true;
                    }
                }

                camera.target = (Vector2){ player.rect.x + player.rect.width / 2 -( screenWidth/2),player.rect.y + player.rect.height / 2 -(screenHeight/2)};
            }
            else 
            {
                if (IsKeyPressed(KEY_R)) 
                {
                    gamemode = 1;
                    player = Player();
                    gameWon = false;
                    
                }
            }
            UpdateMusicStream(gameSound);
        }

        else if (gamemode == 3) 
        {


            for (int i = 0; i < numCollectibles_set1; ++i) {
                collectibles1[i].collected = false;
            }


            for (int i = 0; i < numCollectibles_set2; ++i) 
            {
                collectibles2[i].collected = false;
            }

            // Reset 
            Rectangle birdDefaultPositionsA[] = 
            {
                {1350, 356, birdSize, birdSize},
                {1650, 306, birdSize, birdSize},
                {1950, 256, birdSize, birdSize},
                {2250, 456, birdSize, birdSize},
                {3050, 406, birdSize, birdSize},
                {3350, 356, birdSize, birdSize},
                {3650, 306, birdSize, birdSize},
                {3950, 456, birdSize, birdSize},
                {5250, 356, birdSize, birdSize},
                {6050, 306, birdSize, birdSize},
                {6350, 256, birdSize, birdSize},
                {6650, 206, birdSize, birdSize},
                {6950, 156, birdSize, birdSize}
            };

            for (int i = 0; i < num_bird1; ++i) 
            {
                birds_a[i].isAlive = true;
                birds_a[i].rect = birdDefaultPositionsA[i];
                birds_a[i].b = 0;
                birds_a[i].enemey_run = { 0, 0, 64, 64 };
            }


            // Reset birds
            Rectangle birdDefaultPositionsB[] = {
                {1300, 460, 64, 64},
                {1600, 410, 64, 64},
                {1900, 360, 64, 64},
                {2200, 290, 64, 64},
                {2550, 460, 64, 64},
                {2650, 360, 64, 64},
                {2750, 260, 64, 64},
                {3000, 510, 64, 64},
                {3200, 460, 64, 64},
                {3400, 410, 64, 64},
                {3600, 560, 64, 64},
                {3900, 460, 64, 64},
                {5000, 410, 64, 64},
                {5300, 235, 64, 64},
                {5400, 135, 64, 64},
                {5600, 85, 64, 64},
                {5800, 460, 64, 64},
                {6100, 360, 64, 64},
                {6300, 310, 64, 64},
                {6600, 260, 64, 64},
                {7000, 210, 64, 64}
            };

            for (int i = 0; i < num_bird2; ++i) 
            {
                birds_b[i].isAlive = true;
                birds_b[i].rect = birdDefaultPositionsB[i];
                birds_b[i].b = 0;
                birds_b[i].enemey_run = { 0, 0, 64, 64 };
            }


            if (CheckCollisionPointRec(mousePosition, main) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                gamemode = 0;
                lives = 3;
                score = 0;
            }
            if (CheckCollisionPointRec(mousePosition, restart) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                gamemode = 1;
                lives = 3;
                score = 0;
            }
            if (CheckCollisionPointRec(mousePosition, exit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                CloseWindow();
            }
        }
    }

    void draw(Camera2D camera) 
    {


        if (gamemode == 0) {
            DrawTexture(mainmenu, 0, 0, WHITE);
            int MtextWidth = MeasureText("MAIN MENU", 80);
            DrawText("MAIN MENU", (screenWidth / 2) - (MtextWidth / 2), 100, 80, DARKBLUE);

            DrawRectangleRec(game, RED);

            int textWidth = MeasureText("Normal Game", 20);
            int textHeight = 20;


            DrawText("Normal Game", (int)(game.x + (game.width - textWidth) / 2), (int)(game.y + (game.height - textHeight) / 2), 20, BLACK);

        }
        else if (gamemode == 1) {

            for (int i = 0; i < 2; ++i) {
                DrawTexture(background, (int)(scrollingX + i * background.width), 0, WHITE);
            }
            int x1 = 10;
            int y1 = 10;
            player.draw_lives(heartTexture, x1, y1, lives);



            DrawText(TextFormat("SCORE BOARD: %i", score), screenWidth - 300, 20, 30, RED);

            if (!gameWon) {
                BeginMode2D(camera);


                for (int i = 0; i < Platform_set1; i++) {
                    platform_a[i].draw(groundTexture, largeTexture, floatingTexture, jumpTexture, groundTexture1, largeTexture1, floatingTexture1, jumpTexture2, 1);
                }


                for (int i = 0; i < numCollectibles_set1; i++) {
                    collectibles1[i].draw();
                }


                for (int i = 0; i < maxBullets; i++) {
                    bullets[i].draw();
                }


                player.draw(playerTexture);

                for (int i = 0; i < num_bird1; i++) {
                    birds_a[i].draw(enemey1Texture);
                }

                EndMode2D();
            }
            else {
                DrawText("You Win!", screenWidth / 2 - 100, screenHeight / 2 - 40, 40, GREEN);
                DrawText("Press 'R' to for next level ", screenWidth / 2 - 150, screenHeight / 2 + 20, 20, DARKGRAY);
            }
        }

        else if (gamemode == 4) {

            for (int i = 0; i < 2; ++i) {
                DrawTexture(background1, (int)(scrollingX + i * background1.width), 0, WHITE);
            }
            int x1 = 10;
            int y1 = 10;
            player.draw_lives(heartTexture, x1, y1, lives);



            DrawText(TextFormat("SCORE BOARD: %i", score), screenWidth - 300, 20, 30, RED);

            if (!gameWon) {
                BeginMode2D(camera);


                for (int i = 0; i < Platform_set2; i++) {
                    platform_b[i].draw(groundTexture, largeTexture, floatingTexture, jumpTexture, groundTexture1, largeTexture1, floatingTexture1, jumpTexture2, 2);
                }


                for (int i = 0; i < numCollectibles_set2; i++) {
                    collectibles2[i].draw();
                }


                for (int i = 0; i < maxBullets; i++) {
                    bullets[i].draw();
                }


                player.draw(playerTexture);

                for (int i = 0; i < num_bird2; i++) {
                    birds_b[i].draw(enemey1Texture);
                }

                EndMode2D();
            }
            else {
                DrawText("You Win!", screenWidth / 2 - 100, screenHeight / 2 - 40, 40, GREEN);
                DrawText("Press 'R' for Main Menu ", screenWidth / 2 - 150, screenHeight / 2 + 20, 20, DARKGRAY);
            }
        }


        else if (gamemode == 3) {
            DrawTexture(loosing, 0, 0, WHITE);
            int MtextWidth = MeasureText("YOU LOST", 80);
            DrawText("YOU LOST", (screenWidth / 2) - (MtextWidth / 2), 100, 80, DARKBLUE);

            DrawRectangleRec(main, RED);
            DrawRectangleRec(restart, RED);
            DrawRectangleRec(exit, RED);


            int textWidth = MeasureText("Main Menu", 20);
            int textHeight = 20;
            DrawText("Main Menu", (int)(main.x + (main.width - textWidth) / 2), (int)(main.y + (main.height - textHeight) / 2), 20, WHITE);

            textWidth = MeasureText("Restart", 20);
            DrawText("Restart", (int)(restart.x + (restart.width - textWidth) / 2), (int)(restart.y + (restart.height - textHeight) / 2), 20, WHITE);

            textWidth = MeasureText("Exit", 20);
            DrawText("Exit", (int)(exit.x + (exit.width - textWidth) / 2), (int)(exit.y + (exit.height - textHeight) / 2), 20, WHITE);
        }
    }
};

int main() {

    InitWindow(screenWidth, screenHeight, "Goblin Run");
    SetTargetFPS(30);
    InitAudioDevice();


    Camera2D camera = { {0,0}, {0,0}, 0.0f, 1.0f };
    camera.zoom = 1.0f;


    GameManager gameManager;

    while (!WindowShouldClose()) {

        gameManager.update(camera);


        BeginDrawing();
        ClearBackground(RAYWHITE);
        gameManager.draw(camera);
        EndDrawing();
    }


    CloseAudioDevice();
    CloseWindow();

    return 0;
}