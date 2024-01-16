#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#define width 1150
#define height 600
#define framerate 60
TTF_Font* font;
int main(int argc,char*argv[]) {
    int score = 0;
    int bestscore = 0;
    if (TTF_Init())
    {
        SDL_Log("Can not init ttf, %s", TTF_GetError());
        return 1;
    }
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Can not init wideo ,%s", SDL_GetError());
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("Dinosaur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,height, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        SDL_Log("Can not create window ,%s", SDL_GetError());
        return 1;
    }//创建窗口
    font = TTF_OpenFont("hanyifengshanghei85w.ttf", 64);
    if (font == NULL)
    {
        SDL_Log("Can not open font");
        return 1;
    }//打开字体库

    SDL_Renderer *renderer;
    renderer=SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_Log("Can not create renderer ,%s", SDL_GetError());
        return 1;
    }//创建渲染器

    SDL_Texture* pause = IMG_LoadTexture(renderer,"pause.png");
    SDL_Texture* left = IMG_LoadTexture(renderer, "left.png");
    SDL_Texture* right = IMG_LoadTexture(renderer, "right.png");
    SDL_Texture* down = IMG_LoadTexture(renderer, "down.png");
    SDL_Texture* fly1 = IMG_LoadTexture(renderer, "fly1.png");
    SDL_Texture* fly2 = IMG_LoadTexture(renderer, "fly2.png");
    SDL_Texture* big = IMG_LoadTexture(renderer, "big.png");
    SDL_Texture* big2 = IMG_LoadTexture(renderer, "big2.png");
    SDL_Texture* middle = IMG_LoadTexture(renderer, "middle.png");
    SDL_Texture* small = IMG_LoadTexture(renderer, "small.png");
    SDL_Texture* cloud = IMG_LoadTexture(renderer, "cloud.png");
    SDL_Texture* gameover = IMG_LoadTexture(renderer, "over.png");
    SDL_Texture* ground = IMG_LoadTexture(renderer,"ground.png");
    SDL_Texture* stop = IMG_LoadTexture(renderer, "stop.png");//载入图片
    SDL_Texture* texture0 = NULL;
    SDL_Surface* text0 = NULL;
    SDL_Texture* texture1 = NULL;
    SDL_Surface* text1 = NULL;
    SDL_Texture* texture2 = NULL;
    SDL_Surface* text2 = NULL;
    SDL_Texture* texture3 = NULL;
    SDL_Surface* text3 = NULL;
    SDL_Texture* texture4 = NULL;
    SDL_Surface* text4 = NULL;
    SDL_Texture* texture5 = NULL;
    SDL_Surface* text5 = NULL;
    SDL_Texture* texture6 = NULL;
    SDL_Surface* text6 = NULL;
    bool startgame = false;
    int x1 = -1150;
    int y1 = 160;
    int z1 = 200;
    int a1 = 470;
    int b1 = 250;
    int c1 = 300;
    int d1 = 100;
    int trans = 0;
    SDL_Event event1;       
    while (1) { //开始界面
        long start = SDL_GetTicks();
        if (startgame == false)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            SDL_Color color = { 0,0,0,255 };
            SDL_Rect desRecttext1 = { 400,50,300,100 };
            SDL_RenderCopy(renderer, texture1, NULL, &desRecttext1);
            text1 = TTF_RenderText_Blended(font, "Press Space To Start!", color);
            texture1 = SDL_CreateTextureFromSurface(renderer, text1);

            SDL_Rect desRecta = { a1,b1,y1,z1 };
            SDL_RenderCopy(renderer, pause, NULL, &desRecta);

            SDL_Rect desRectb = { x1,450,1150,30 };
            SDL_RenderCopy(renderer, ground, NULL, &desRectb);
        }
        else {//逐步过度到游戏界面
            if (trans != 20)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                SDL_Color color = { 0,0,0,255 };
                SDL_Rect desRecttext1 = { 400,50,c1,d1 };
                c1 = c1 - 15;
                d1 = d1 - 5;
                SDL_RenderCopy(renderer, texture1, NULL, &desRecttext1);
                text1 = TTF_RenderText_Blended(font, "Press Space To Start!", color);
                texture1 = SDL_CreateTextureFromSurface(renderer, text1);

                SDL_Rect desRecta = { a1,b1,y1,z1 };
                a1 = a1 - 21;
                b1 = b1 + 5;
                y1 = y1 - 4;
                z1 = z1 - 9.5;
                SDL_RenderCopy(renderer, pause, NULL, &desRecta);

                SDL_Rect desRectb = { x1,450,1150,30 };
                x1 = x1 + 57.5;
                SDL_RenderCopy(renderer, ground, NULL, &desRectb);
                trans++;
            }
            else break;
        }

        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event1))
        {
            if (event1.type == SDL_QUIT)
            {
                return;
            }
            if (event1.key.keysym.sym == SDLK_SPACE)startgame=true;
        }
        long now = SDL_GetTicks();
        long time = now - start;
        long frame = 1000 / framerate;
        long delay = frame - time;
        if (delay > 0) SDL_Delay(delay);
    }
    bool again = false;

loop:     score = 0;
    int change = 0;
    int interval = 700;
    bool jump = false;
    bool bend = false;
    bool hurdlebig = false;
    bool hurdlebig2 = false;
    bool hurdlemiddle = false;
    bool hurdlesmall = false;
    bool hurdlefly = false;
    bool gameisover = false;
    bool ifdown = false;
    bool invincible = false;
    bool flying = false;
    bool downing = false;
    bool ifpause = false;
    int xcloud1 = 1150;
    int ycloud1 = rand() % 130 + 20;
    int xcloud2 = rand()%500+100;
    int ycloud2 = rand() % 130 + 20;
    int xfly = 1150;
    int yfly = rand() % 300 + 120;
    int xbig = 1150;
    int xbig2 = 1150;
    int xmiddle = 1150;
    int xsmall = 1150;
    int speed=10;
    int groundx1 = 0,groundx2 = 1150;
    int jumpy = 350;
    int ychange = 1;        
    int max = 18;
    char* a = (char*)malloc(6 * sizeof(char));
    char *b= (char*)malloc(6 * sizeof(char));
    SDL_Point center;
    SDL_Point rightcorner;
    SDL_Point leftcorner;
    gameisover = false;
    while (gameisover==false)//游戏界面
    {
        long start = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);


        if (flying == false)
        {
            if (jump == true) {
                if (bend == true && ifdown == false) {
                    if (ychange < 18) max = ychange;
                    ifdown = true;
                }
                if (ychange < max) {
                    jumpy = jumpy - 13;
                    ychange++;
                }
                else if (ychange < 2 * max - 1) {
                    jumpy = jumpy + 13;
                    ychange++;
                }
                else {
                    ychange = 1;
                    jump = false;
                    ifdown = false;
                    max = 18;
                }
            }//跳跃
            SDL_Rect desRectup = { 50,jumpy,80,100 };
            SDL_Rect desRectdown = { 50,390,100,60 };
            if (bend == false)
            {
                if (change % 41 <= 20) SDL_RenderCopy(renderer, left, NULL, &desRectup);
                else SDL_RenderCopy(renderer, right, NULL, &desRectup);//小恐龙跑动
                center.x = 90;
                center.y = jumpy + 50;
                rightcorner.x = 130 - 3;
                rightcorner.y = jumpy + 3;
                leftcorner.x = 50 + 10;
                leftcorner.y = jumpy + 100 - 10;//取碰撞检测点
            }
            else {
                if (jump == false) {
                    SDL_RenderCopy(renderer, down, NULL, &desRectdown);
                    center.x = 100;
                    center.y = 420;
                    rightcorner.x = 150 - 3;
                    rightcorner.y = 390 + 3;
                    leftcorner.x = 50 + 10;
                    leftcorner.y = 450 - 10;//取碰撞检测点
                }
                else {
                    if (change % 41 <= 20) SDL_RenderCopy(renderer, left, NULL, &desRectup);
                    else SDL_RenderCopy(renderer, right, NULL, &desRectup);//小恐龙跑动
                    center.x = 90;
                    center.y = jumpy + 50;
                    rightcorner.x = 130 - 3;
                    rightcorner.y = jumpy + 3;
                    leftcorner.x = 50 + 10;
                    leftcorner.y = jumpy + 100 - 10;//取碰撞检测点
                }
            }
        }
        else {//飞行模式
            jump = false;
            ifdown = false;
            if (downing == false)
            {
                SDL_Rect desRectup = { 50,jumpy,80,100 };
                if (jumpy > 0) {
                    jumpy = jumpy - 5;
                    if (change % 41 <= 20) SDL_RenderCopy(renderer, left, NULL, &desRectup);
                    else SDL_RenderCopy(renderer, right, NULL, &desRectup);
                }
                else {
                    SDL_Rect desRecta = { 50,0,80,100 };
                    SDL_RenderCopy(renderer, pause, NULL, &desRecta);
                }
                center.x = 0;
                center.y = 0;
                rightcorner.x = 0;
                rightcorner.y = 0;
                leftcorner.x = 0;
                leftcorner.y = 0;
            }
            else{
            SDL_Rect desRectup = { 50,jumpy,80,100 };
            if (jumpy < 350) {
                jumpy = jumpy + 5;
                if (change % 41 <= 20) SDL_RenderCopy(renderer, left, NULL, &desRectup);
                else SDL_RenderCopy(renderer, right, NULL, &desRectup);
            }
            else {
                jumpy = 350;
                flying = false;
                downing = false;
            }
            center.x = 0;
            center.y = 0;
            rightcorner.x = 0;
            rightcorner.y = 0;
            leftcorner.x = 0;
            leftcorner.y = 0;//取碰撞检测点
        }
        }


        //地面
        SDL_Rect desRectground1 = { groundx1,450,1150,30 };
        SDL_Rect desRectground2 = { groundx2,450,1150,30 };
        SDL_RenderCopy(renderer, ground, NULL, &desRectground1);
        SDL_RenderCopy(renderer, ground, NULL, &desRectground2);
        groundx1 = groundx1 - speed;
        groundx2 = groundx2 - speed;
        if (groundx1 < -1150)groundx1 = 0;
        if (groundx2 < 0)groundx2 = 1150;

        //障碍物随机生成
        int hurdle = rand() % 10;
        if (xbig < -115) {
            xbig = 1150;
            hurdlebig = false;
        }
        if (xsmall < -115) {
            xsmall = 1150;
            hurdlesmall = false;
        }
        if (xbig2 <-130) {
            xbig2 = 1150;
            hurdlebig2 = false;
        }
        if (xmiddle <-100) {
            xmiddle = 1150;
            hurdlemiddle = false;
        }
        SDL_Rect desRectbig = { xbig,360,100,100 };
        SDL_Rect desRectsmall = { xsmall,360,52,100 };
        SDL_Rect desRectbig2 = { xbig2,360,100,100 };
        SDL_Rect desRectmiddle = { xmiddle,360,80,100 };
        if (hurdle == 3) {
            if (hurdlebig == false) 
                if (hurdlesmall == false || xsmall < interval)
                    if (hurdlefly == false || xfly < interval)
                        if (hurdlebig2 == false || xbig2 < interval)
                            if (hurdlemiddle == false || xmiddle < interval)hurdlebig = true;
        }
        if (hurdle == 7) {
            if (hurdlebig2 == false)
                if (hurdlesmall == false || xsmall < interval)
                    if (hurdlefly == false || xfly < interval)
                        if (hurdlebig == false || xbig < interval)
                            if (hurdlemiddle == false || xmiddle < interval)hurdlebig2 = true;
        }
        if (hurdle == 0) {
            if (hurdlesmall == false)
                if ( hurdlebig == false|| xbig < interval)
                    if (hurdlefly == false || xfly < interval)
                        if (hurdlebig2 == false || xbig2 < interval)
                            if (hurdlemiddle == false || xmiddle < interval)hurdlesmall = true;
        }
        if (hurdle == 9) {
            if (hurdlemiddle == false)
                if (hurdlesmall == false || xsmall < interval)
                    if (hurdlefly == false || xfly < interval)
                        if (hurdlebig2 == false || xbig2 < interval)
                            if (hurdlebig == false || xbig < interval)hurdlemiddle = true;
        }
        if (hurdlebig == true)
        {
            SDL_RenderCopy(renderer, big, NULL, &desRectbig);
            if (invincible == false)
            {
                //碰撞检测
                if (center.x >= xbig && center.x <= xbig + 100 - 6 && center.y >= 360 && center.y <= 460)gameisover = true;
                if (rightcorner.x >= xbig && rightcorner.x <= xbig + 100 - 6 && rightcorner.y >= 360 && rightcorner.y <= 460)gameisover = true;
                if (leftcorner.x >= xbig && leftcorner.x <= xbig + 100 - 6 && leftcorner.y >= 360 && leftcorner.y <= 460)gameisover = true;
            }
            xbig = xbig - speed;
        }
        if (hurdlesmall == true)
        {
            SDL_RenderCopy(renderer, small, NULL, &desRectsmall);
            if (invincible == false)
            {
                //碰撞检测
                if (center.x >= xsmall && center.x <= xsmall + 52 - 8 && center.y >= 360 + 8 && center.y <= 460)gameisover = true;
                if (rightcorner.x >= xsmall && rightcorner.x <= xsmall + 52 - 8 && rightcorner.y >= 360 + 8 && rightcorner.y <= 460)gameisover = true;
                if (leftcorner.x >= xsmall && leftcorner.x <= xsmall + 52 - 8 && leftcorner.y >= 360 + 8 && leftcorner.y <= 460)gameisover = true;
            }
            xsmall = xsmall - speed;
        }
        if (hurdlebig2 == true)
        {
            SDL_RenderCopy(renderer, big2, NULL, &desRectbig2);
            if (invincible == false)
            {
                //碰撞检测
                if (center.x >= xbig2 && center.x <= xbig2 + 100 - 4 && center.y >= 360 + 4 && center.y <= 460)gameisover = true;
                if (rightcorner.x >= xbig2 && rightcorner.x <= xbig2 + 100 - 4 && rightcorner.y >= 360 + 4 && rightcorner.y <= 460)gameisover = true;
                if (leftcorner.x >= xbig2 && leftcorner.x <= xbig2 + 100 - 4 && leftcorner.y >= 360 + 4 && leftcorner.y <= 460)gameisover = true;
            }
            xbig2 = xbig2 - speed;
        }
        if (hurdlemiddle == true)
        {
            SDL_RenderCopy(renderer, middle, NULL, &desRectmiddle);
            if (invincible == false)
            {
                //碰撞检测
                if (center.x >= xmiddle && center.x <= xmiddle + 100 - 5 && center.y >= 360 + 5 && center.y <= 460)gameisover = true;
                if (rightcorner.x >= xmiddle && rightcorner.x <= xmiddle + 100 - 5 && rightcorner.y >= 360 + 5 && rightcorner.y <= 460)gameisover = true;
                if (leftcorner.x >= xmiddle && leftcorner.x <= xmiddle + 100 - 5 && leftcorner.y >= 360 + 5 && leftcorner.y <= 460)gameisover = true;
            }
            xmiddle = xmiddle - speed;
        }


        //飞行障碍物随机生成
        if (score>500) {
            if (hurdlefly == false)
                if (hurdlesmall == false || xsmall < interval)
                    if (hurdlemiddle == false || xmiddle < interval)
                        if (hurdlebig2 == false || xbig2 < interval)
                            if (hurdlebig == false || xbig < interval)hurdlefly = true;
        }
        if (hurdlefly == true) {
            if (xfly < -48) {
                yfly = rand() % 300 + 120;
                xfly = 1150;
                hurdlefly = false;
            }
            SDL_Rect desRectfly = { xfly,yfly,48,38 };
            xfly = xfly - speed;
            if (change % 35 <= 17) SDL_RenderCopy(renderer, fly1, NULL, &desRectfly);
            else SDL_RenderCopy(renderer, fly2, NULL, &desRectfly);
            if (invincible == false)
            {
                //碰撞检测
                if (center.x >= xfly && center.x <= xfly + 48 && center.y >= yfly && center.y <= yfly + 38)gameisover = true;
                if (rightcorner.x >= xfly && rightcorner.x <= xfly + 48 && rightcorner.y >= yfly && rightcorner.y <= yfly + 38)gameisover = true;
                if (leftcorner.x >= xfly && leftcorner.x <= xfly + 48 && leftcorner.y >= yfly && leftcorner.y <= yfly + 38)gameisover = true;
            }
        }


        //云朵1
        if (xcloud1 < -75) {
            ycloud1 = rand() % 130 + 20;
            xcloud1 = 1150;
        }
        SDL_Rect desRectcloud1 = { xcloud1,ycloud1,100,72 };
        xcloud1=xcloud1-2;
        SDL_RenderCopy(renderer, cloud, NULL, &desRectcloud1);

        //云朵2
        if (xcloud2 < -75) {
            ycloud2 = rand() % 130 + 20;
            xcloud2 = 1150;
        }
        SDL_Rect desRectcloud2 = { xcloud2,ycloud2,100,72 };
        xcloud2 = xcloud2 - 2;
        SDL_RenderCopy(renderer, cloud, NULL, &desRectcloud2);
                

        //计分板
        SDL_Color color = { 0,0,0,255 };
        text5 = TTF_RenderText_Blended(font, "Score:", color);
        texture5 = SDL_CreateTextureFromSurface(renderer, text5);
        SDL_Rect desRecttext5 = { 1000,0,75,50 };
        SDL_RenderCopy(renderer, texture5, NULL, &desRecttext5);
        sprintf_s(a, sizeof(a),"%06d", score);
        text2 = TTF_RenderUTF8_Blended(font, a, color);
        texture2= SDL_CreateTextureFromSurface(renderer, text2);
        SDL_Rect desRecttext2 = { 1075,0,75,50 };
        SDL_RenderCopy(renderer, texture2, NULL, &desRecttext2);


        //最好成绩
        if (again == true)
        {
            text6 = TTF_RenderText_Blended(font, "Best Score:", color);
            texture6 = SDL_CreateTextureFromSurface(renderer, text6);
            SDL_Rect desRecttext6 = { 940,50,135,50 };
            SDL_RenderCopy(renderer, texture6, NULL, &desRecttext6);

            sprintf_s(b, sizeof(b), "%06d", bestscore);
            text3 = TTF_RenderUTF8_Blended(font, b, color);
            texture3 = SDL_CreateTextureFromSurface(renderer, text3);
            SDL_Rect desRecttext3 = { 1075,50,75,50 };
            SDL_RenderCopy(renderer, texture3, NULL, &desRecttext3);
        }


        //无敌模式
        if (invincible == true)
        {
            text4 = TTF_RenderUTF8_Blended(font, "Invincible Mode", color);
            texture4 = SDL_CreateTextureFromSurface(renderer, text4);
            SDL_Rect desRecttext4 = { 500,100,150,50 };
            SDL_RenderCopy(renderer, texture4, NULL, &desRecttext4);
        }

        //飞行模式
        if (flying == true)
        {
            text0 = TTF_RenderUTF8_Blended(font, "Flying Mode", color);
            texture0 = SDL_CreateTextureFromSurface(renderer, text0);
            SDL_Rect desRecttext0 = { 500,150,150,50 };
            SDL_RenderCopy(renderer, texture0, NULL, &desRecttext0);
        }


        //暂停
        loop1:if (ifpause == true)
        {
            SDL_Rect desRectstop = { 500,200,100,100 };
            SDL_RenderCopy(renderer, stop, NULL, &desRectstop);
        }
        
        SDL_RenderPresent(renderer);


        //事件判断
        SDL_Event event2;
                while (SDL_PollEvent(&event2))
        {
            if(event2.type==SDL_QUIT)return;
            else if(event2.type==SDL_MOUSEBUTTONDOWN) {
                if (ifpause == false)ifpause = true;
                else ifpause = false;
            }
            else {
                switch (event2.key.keysym.sym)
                {
                case SDLK_SPACE: {jump = true;
                    break; }
                case SDLK_UP: {jump = true;
                    break; }
                case SDLK_DOWN: {if(ifdown==false)bend = true;
                    break; }
                case SDLK_g: {
                    break;
                }
                case SDLK_f: {
                    break;
                }
                default:break;
                }
            }
            if (event2.type == SDL_KEYUP) { 
                if(event2.key.keysym.sym==SDLK_DOWN)bend = false; 
                if (event2.key.keysym.sym == SDLK_g) {
                    if (invincible == false)invincible = true;
                    else invincible = false;
                }
                if (event2.key.keysym.sym == SDLK_f) {
                    if (flying == false)flying = true;
                    else downing = true;
                }
            }
        }

                if (ifpause == true)goto loop1;

        change++;
        score++;

        //速度控制
        if (score % 500 == 0) {
            speed = speed + 2;
            interval = interval - 50;
        }
        


       //帧率控制
        long now = SDL_GetTicks();
        long time = now - start;
        long frame = 1000 / framerate;
        long delay = frame - time;
        if(delay>0) SDL_Delay(delay);
    }


    bool ifloop = false;        
    SDL_Event event3;
    while (1)//结束界面
    {
        SDL_Rect desRectc = { 400,150,300,130 };
        SDL_RenderCopy(renderer, gameover, NULL, &desRectc);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event3))
        {
            if (event3.type == SDL_QUIT)
            {
                return;
            }
            if (event3.key.keysym.sym == SDLK_SPACE){
                if (score > bestscore)
                {
                    bestscore = score;
                }
                ifloop = true;
                again = true;
                break;
            }
        }
    }
    if (ifloop = true) {
        ifloop = false;
        goto loop;
    }
    
    
    //销毁
    SDL_DestroyTexture(pause);
    SDL_DestroyTexture(left);
    SDL_DestroyTexture(right);
    SDL_DestroyTexture(down);
    SDL_DestroyTexture(fly1);
    SDL_DestroyTexture(fly2);
    SDL_DestroyTexture(big);
    SDL_DestroyTexture(big2);
    SDL_DestroyTexture(middle);
    SDL_DestroyTexture(small);
    SDL_DestroyTexture(cloud);
    SDL_DestroyTexture(ground);
    SDL_DestroyTexture(stop);
    SDL_DestroyTexture(gameover);
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);
    SDL_DestroyTexture(texture6);
    SDL_DestroyTexture(texture0);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(win);
    return 0;
}
