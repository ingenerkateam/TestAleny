#include "tinyxml/tinystr.h"
#include "tinyxml/tinystr.cpp"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinyxml.cpp"
#include "tinyxml/tinyxmlerror.cpp"
#include "tinyxml/tinyxmlparser.cpp"
#include "TXLib.h"

#include <iostream>
#include <clocale>

struct Answer
{
    int x;
    int y;
    const char* text;
    int radius;
};

struct Question
{
    int         qx;
    int         qy;
    const char* question_text;
    const char* file_address;
    int         count_of_answers;
    int         pravilnyi_otvet;
    int         otvet_cheloveka;
    Answer      otvety[10];
};

int zapolnit_massiv(Question* questions)
{
    int current_question = -1;
    int current_answer = -1;
    setlocale(LC_ALL, "Russian"); // вызов функции настройки локали
    // Загружаем xml с кодировкой UTF-8
    TiXmlDocument document("database2.txt");
    document.LoadFile(TIXML_ENCODING_UNKNOWN);

    // Загружаем категорию "<database>"
    TiXmlElement *database = document.FirstChildElement("Voprosy");
    if (database)
    {
        // Загружаем категорию "<user>" по этапно
        for (TiXmlElement *user = database->FirstChildElement("question"); user; user = user->NextSiblingElement("question"))
        {
            current_question = current_question + 1;
            current_answer = -1;
            // Получаем qx
            const char *qx = user->Attribute("qx");
            if (qx)
            {
                questions[current_question].qx = atoi(qx);
                //std::cout << "Qx: " << qx << std::endl;
            }
            // Получаем qy
            const char *qy = user->Attribute("qy");
            if (qy)
            {
                questions[current_question].qy = atoi(qy);
                //std::cout << "Qy: " << qy << std::endl;
            }
             // Получаем question_text
            const char *question_text = user->Attribute("question_text");
            if (question_text)
            {
                questions[current_question].question_text = question_text;
                //std::cout << "question_text: " << question_text << std::endl;
            }
             // Получаем file_address
            const char *file_address = user->Attribute("file_address");
            if (file_address)
            {
                questions[current_question].file_address = file_address;
                //std::cout << "file_address: " << file_address << std::endl;
            }
            // Получаем count_of_answers
            const char *count_of_answers = user->Attribute("count_of_answers");
            if (count_of_answers)
            {
                questions[current_question].count_of_answers = atoi(count_of_answers);
                //std::cout << "count_of_answers: " << count_of_answers << std::endl;
            }
             // Получаем pravilnyi_otvet
            const char * pravilnyi_otvet = user->Attribute("pravilnyi_otvet");
            if ( pravilnyi_otvet)
            {
                questions[current_question].pravilnyi_otvet = atoi(pravilnyi_otvet);
                //std::cout << "pravilnyi_otvet: " <<  pravilnyi_otvet << std::endl;
            }
            // Получаем otvet_chelovekat
            const char *otvet_chelovekat = user->Attribute("otvet_chelovekat");
            if ( otvet_chelovekat)
            {

                questions[current_question].otvet_cheloveka = atoi(otvet_chelovekat);
                //std::cout << "otvet_chelovekat: " << otvet_chelovekat << std::endl;
            }

        // Загружаем категорию "<otvety >"
        //TiXmlElement *userdata = user->FirstChildElement("otvety");

            for (TiXmlElement *userdata = user->FirstChildElement("otvety"); userdata; userdata = userdata->NextSiblingElement("otvety"))
            //if (userdata)
            {
                current_answer = current_answer + 1;
                // Получаем x
                const char *x = userdata->Attribute("x");
                if (x)
                {
                    questions[current_question].otvety[current_answer].x = atoi (x);
                    //std::cout << "x: " << x << std::endl;
                }

                 // Получаем y
                const char *y = userdata->Attribute("y");
                if (y)
                {

                    questions[current_question].otvety[current_answer].y = atoi (y);
                    //std::cout << "y: " << y << std::endl;
                }

                // Получаем text
                const char *text = userdata->Attribute("text");
                if (text)
                {
                    questions[current_question].otvety[current_answer].text = text;
                    //std::cout << "text: " << text << std::endl;
                }

                // Получаем radius
                const char *radius = userdata->Attribute("radius");
                if (radius)
                {

                    questions[current_question].otvety[current_answer].radius = atoi (radius);
                    //std::cout << "radius: " << radius << std::endl;
                }
            }

            //std::cout << std::endl;
        }
    }

    return 0;
}
