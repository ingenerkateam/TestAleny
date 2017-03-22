#include "TXLib.h"
#include "main18.cpp"

#include <fstream>
using namespace std;

Question questions[100];
const int COUNT_OF_ANSWER = 6;
const int COUNT_OF_QUESTION = 8;


void fon ( int x, int y, HDC* fon_vopros);
void play ();
void draw_question (Question *question);
void draw_answer (Answer* otvet);
//Question voprosy(int nomervoprosa);
void draw (int x, int y, HDC* fon_vopros, int* otvety);
void button (int bx, int by, int bx1, int by1, const char* arrow);
bool transition (int bx, int by, int bx1, int by1, HDC* fon_vopros, Question *question, int* nomervoprosa);
void draw_end (int* otvety);


int main()
{
    txCreateWindow ( 500, 650);
    zapolnit_massiv(questions);
    play ();


    return 0;
}

void fon ( int x, int y, HDC* fon_vopros)
{
    txBitBlt (txDC(), x, y, txGetExtentX (), txGetExtentY (), *fon_vopros, 0, 0);
}

void draw_answer (Answer* otvet)
{
    txSetFillColor (TX_WHITE);
    txSetColor (TX_BLACK);
    txCircle (otvet->x - 20, otvet->y + 20, otvet->radius);
    txSelectFont ("Comic Sans MS", 40);

    txTextOut (otvet->x, otvet->y, otvet->text);
}

void draw_question (Question *question)
{
    HDC fon_vopros = txLoadImage (question->file_address);
    int summa = 0;

    fon(0, 0, &fon_vopros);
    txSetFillColor (TX_RED);
    txSetColor (TX_BLACK);
    txSelectFont ("Comic Sans MS", 40);

    txTextOut (question->qx, question->qy, question->question_text);

    for (int i = 0; i < question->count_of_answers; i++) {
        draw_answer (&question->otvety[i]);

        if (question->otvet_cheloveka == question->pravilnyi_otvet and
            question->otvet_cheloveka == i + 1) {
            txSetFillColor(TX_RED);
            txCircle (question->otvety[i].x - 20, question->otvety[i].y + 20, 3);
            summa = summa + 1;

            txSleep(100);
        }
    }

    txDeleteDC (&fon_vopros);
}

Question voprosy(int nomervoprosa)
{/*
     Question questions[COUNT_OF_QUESTION + 1];

     questions[1] = {100,  100, "Тест",  "конец теста.bmp", 1, 0, 0, {{100, 200, "Начать тест", 7}}};

     questions[2] = {100,  100, "Ваш вопрос1",  "океан.bmp", 2, 2, 0, {{100, 200, "dsfg", 7},
                                                                       {100, 280, "dsfg", 7}}};

     questions[3] = {100,  100, "Ваш вопрос2",  "океан2.bmp", 3, 2, 0, {{100, 200, "dsfdhgg", 7},
                                                                       {100, 280, "45678", 7},
                                                                       {100, 360, "78625", 7}}};

     questions[4] = {100,  100, "Ваш вопрос3",  "океан.bmp", 3, 2, 0, {{100, 200, "jndtn", 7},
                                                                       {100, 280, "849779", 7},
                                                                       {100, 360, "45678", 7}}};

     questions[5] = {100,  100, "Ваш вопрос4",  "океан2.bmp", 3, 2, 0, {{100, 200, "jndtn", 7},
                                                                       {100, 280, "ftghjfg", 7},
                                                                       {100, 360, "ftghjfg", 7}}};

     questions[6] = {100,  100, "Ваш вопрос5",  "океан.bmp", 4, 2, 0, {{100, 200, "dsfg", 7},
                                                                       {100, 280, "dsfdhgg", 7},
                                                                       {100, 360, "dsfdhgg", 7},
                                                                       {100, 440, "49684", 7}}};

     questions[7] = {100,  100, "Ваш вопрос6",  "океан2.bmp", 4, 2, 0, {{100, 200, "dsfg", 7},
                                                                       {100, 280, "dsfdhgg", 7},
                                                                       {100, 360, "45678", 7},
                                                                       {100, 440, "78625", 7}}};

     questions[8] = {100,  100, "Ваш вопрос7",  "океан2.bmp", 3, 2, 0, {{100, 200, "dsfg", 7},
                                                                        {100, 280, "78625", 7},
                                                                        {100, 360, "45648", 7}}};

    questions[9] = {100,  100, "Тест пройден!",  "конец теста.bmp", 1, 2, 0, {{100, 200, "Результаты", 0}}};
*/

    if (nomervoprosa > COUNT_OF_QUESTION) {
        return questions[COUNT_OF_QUESTION];
    }
    return questions[nomervoprosa];
}


void draw (int x, int y, HDC* fon_vopros, int* otvety)
{
    int tx = 80;
    int ty = 220;
    int x1;
    int y1;
    int nomervoprosa = 0;

    Question question = voprosy(nomervoprosa);
    draw_question (&question);

    while(!(GetAsyncKeyState(VK_ESCAPE) or nomervoprosa == COUNT_OF_QUESTION))
    {
        question = voprosy(nomervoprosa);

        for (int i = 0; i < question.count_of_answers; i++) {
            x1 = tx;
            y1 = ty + 80*i;
//i+1 - номер ответа
//Правильный ответ question.pravilnyi_otvet
            if ((txMouseButtons() & 1) && (txMouseY() > y1 - 10 && txMouseY() < y1 + 10))
            {
                question.otvet_cheloveka = i + 1;
                otvety[nomervoprosa] = i + 1;
                if (question.pravilnyi_otvet == question.otvet_cheloveka)
                {
                    txSetFillColor(TX_RED);
                    txCircle (x1, y1, 3);
                    txSleep (25);
                }
                draw_question (&question);
                txSetFillColor(TX_BLACK);
                txCircle (x1, y1, 3);
                button (350, 500, 500, 650, "Вперед");

                txSleep (50);
            }
        }

        if (transition (350, 500, 500, 650, fon_vopros, &question, &nomervoprosa)) {

            question = voprosy(nomervoprosa);

            txTextOut (250, 400, "Надо подумать...");
            txSleep(1000);
            draw_question (&question);
        }

        txSleep(10);
    }


    txSleep(300);
}


void button (int bx, int by, int bx1, int by1, const char* arrow)
{
    txSetFillColor (TX_BLACK);
    txSetColor (TX_BLUE);
    txSetFillColor (TX_BLACK);
    txSelectFont ("Comic Sans MS", 40);
    txDrawText (bx, by, bx1, by1, arrow);
}

bool transition (int bx, int by, int bx1, int by1, HDC* fon_vopros, Question *question, int* nomervoprosa)
{
   if ((txMouseButtons() & 1) && (txMouseX() > bx && txMouseX() < bx1 &&
                                  txMouseY() > by && txMouseY() < by1))
   {
        *nomervoprosa = *nomervoprosa + 1;

        txSleep (50);
        return true;
    }
    return false;
}

void draw_end (int * otvety)
{
    txSelectFont ("Comic Sans MS", 50);
//1 вопрос - вступление. Ответ на него не важен
//последний вопрос - заключение. Ответ на него не важен
    int summa = 0;
    int mark = 0;

    for (int i = 2; i < COUNT_OF_QUESTION; i++) {
        Question question = voprosy(i);
        //char vremya[100];
        //sprintf(vremya, "Ваш ответ = %d. Правильный ответ = %d", otvety[i], question.pravilnyi_otvet);

        if (question.pravilnyi_otvet == otvety[i])
        {
            summa = summa + 1;
        }
        //txTextOut(25, 220 + 30*i, vremya);
    }
    char stroka_summa[100];
    sprintf(stroka_summa, "Сумма баллов = %d", summa);
    txTextOut(50, 300, stroka_summa);


    if ( ROUND (100 * summa / (COUNT_OF_QUESTION - 2)) >= 85)
    {
         mark = 5;
    }
    else if (  ROUND (100 * summa / (COUNT_OF_QUESTION - 2)) >= 60)
    {
         mark = 4;
    }
    else if (  ROUND (100 * summa / (COUNT_OF_QUESTION - 2)) >= 40)
    {
         mark = 3;
    }
    else
    {
         mark = 2;
    }

    char stroka_mark[100];
    sprintf(stroka_mark, "Ваша оценка = %d", mark);

    txTextOut(50, 400, stroka_mark);
}

void play ()
{
    HDC fon_vopros = txLoadImage ("океан.bmp");
    int x = 0;
    int y = 0;
    int summa = 0;
    int otvety[COUNT_OF_QUESTION + 1];


    draw (x,  y, &fon_vopros, otvety);
    draw_end(otvety);

    txDeleteDC (&fon_vopros);
}
