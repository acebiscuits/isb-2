#include <iostream>
#include <random>
#include <cassert>
#include <cmath>
using namespace std;
struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG& generator)
{
    std::random_device device;
    generator.engine.seed(device());
}


int randomU(PRNG& generator, int minValue, int maxValue)
{
    assert(minValue < maxValue);
    std::uniform_int_distribution<int> distribution(minValue, maxValue);
    return distribution(generator.engine);
}


float getRandomFloat(PRNG& generator, float minValue, float maxValue)
{
    assert(minValue < maxValue);
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

int main()
{
    PRNG generator;
    initGenerator(generator);


    int line[128];
    int sum_test_1 = 0;

    for (int i = 0; i < 128; ++i)
    {
        line[i] = randomU(generator, 0, 1);
        cout << line[i];
        if (line[i] == 1) { sum_test_1 += 1; }
        else sum_test_1 -= 1;
    }
    double res_test_1 = sum_test_1 / sqrt(128);
    double P;
    P = erfc(res_test_1 / (sqrt(2)));
    cout << endl << "P: " << P << endl;
    ///////////////////
    double sum_test_2 = 0;
    double changes = 0;
    for (int i = 0; i < 128; ++i)
    {

        if (line[i] == 1)sum_test_2 += 1;

    }
    double once_test_2 = sum_test_2 / 128;
    double P_2;

    if (abs(once_test_2 - (1 / 2)) < (2 / (sqrt(128))))
    {
        P_2 = 0;
    }
    else
    {
        for (int i = 0; i < 127; i++)
        {
            if (line[i] == line[i + 1])changes += 0;
            else changes += 1;
        }
        P_2 = erfc((abs(changes - 2 * 128 * once_test_2 * (1 - once_test_2))) / (2 * sqrt(2 * 128) * once_test_2 * (1 - once_test_2)));

    }
    cout << "P2: " << P_2 << endl;
    ////////////////
    double counter_test_3 = 1;
    double max_counter_test_3 = 1;
    int no_one = 0;
    double v1, v2, v3, v4;
    v1 = v2 = v3 = v4 = 0;

    for (int i = 0; i < 16; i++)
    {
        counter_test_3 = 1;
        max_counter_test_3 = 0;
        for (int j = 8 * i; j < 8 * i + 7; j++)
        {
            if (line[j] == 1)
                no_one = 1;

            if (line[j] == 1 && line[j + 1] == 1)
            {
                counter_test_3 += 1;

            }

            if (line[j] == 0)
            {
                if (counter_test_3 > max_counter_test_3)
                {
                    max_counter_test_3 = counter_test_3;
                }
                counter_test_3 = 1;
            }

        }
        if (no_one == 0)
        {
            max_counter_test_3 = 0;
        }
        if (counter_test_3 > max_counter_test_3)
        {
            max_counter_test_3 = counter_test_3;
        }
        if (max_counter_test_3 == 0 || max_counter_test_3 == 1)
        {
            v1 += 1;
        }
        else if (max_counter_test_3 == 2)
        {
            v2 += 1;
        }
        else if (max_counter_test_3 == 3)
        {
            v3 += 1;
        }
        else if (max_counter_test_3 >= 4)
        {
            v4 += 1;
        }
    }
    double pi1, pi2, pi3, pi4;
    pi1 = 0.2148;
    pi2 = 0.3672;
    pi3 = 0.2305;
    pi4 = 0.1875;
    double X2;
    X2 = (pow((v1 - 16 * pi1), 2) / (16 * pi1)) + (pow((v2 - 16 * pi2), 2) / (16 * pi2)) + (pow((v3 - 16 * pi3), 2) / (16 * pi3)) + (pow((v4 - 16 * pi4), 2) / (16 * pi4));

    cout << "X^2: " << X2;

    return 0;
}