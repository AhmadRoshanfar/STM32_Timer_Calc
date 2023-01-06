#include <stdio.h>
#include <math.h>

void logError(const char *string)
{
    printf("\033[0;31m"); /* Red Color*/
    printf("%s", string);
    printf("\033[0m"); /* Defualt Color*/
}

void logInfo(const char *string)
{
    printf("\033[0;35m"); /* Yellow Color*/
    printf("%s", string);
    printf("\033[0m"); /* Defualt Color*/
}

void read_input(int *input)
{
    char term;
    if (scanf("%d%c", input, &term) != 2 || term != '\n')
    {
        logError("Enter an Integer Value\n");
        read_input(input);
    }
}

int main()
{
    int timer_ms = 0;
    int timer_us = 0;
    double timer = 0;
    int timer_freq_MHz = 0;
    double timer_freq = 0;
    int timer_bits = 0;
    double cnt_clk = 0;
    int prescaler = 0;
    double time_period;
    double period_value;
    double limit = 0;
    int mode = 0;

    printf("\n 1. Milliseconds(mS) \n 2. Microseconds(uS) \n");
    printf("Choose timer scale: (1 or 2) ");
    read_input(&mode);
    while (!(mode != 1 ^ mode != 2))
    {
        printf("\n 1. Milliseconds(mS) \n 2. Microseconds(uS) \n");
        printf("Choose timer scale: (1 or 2) ");
        read_input(&mode);
    }
    if (mode == 1)
    {
        printf("\n Timer(ms): ");
        read_input(&timer_ms);
        while (timer_ms < 0)
        {
            printf("Please enter value greater than 0 \n");
            printf("\n Timer(ms): ");
            read_input(&timer_ms);
        }

        timer = timer_ms * pow(10, -3);
    }
    else if (mode == 2)
    {
        printf("\n Timer(us): ");
        read_input(&timer_us);
        while (timer_us < 0)
        {
            printf("Please enter value greater than 0 \n");
            printf("\n Timer(ms): ");
            read_input(&timer_us);
        }
        timer = timer_us * pow(10, -6);
    }

    printf(" Timer Frequcny(MHz): ");
    read_input(&timer_freq_MHz);
    timer_freq = (timer_freq_MHz * pow(10, 6));

    printf(" Number of timer bits (16 or 32): ");
    read_input(&timer_bits);
    while (!(timer_bits != 16 ^ timer_bits != 32))
    {
        logError(" Number of timer bits must be 16 or 32 bits\n");
        printf(" Number of timer bits (16 or 32): ");
        scanf("%d", &timer_bits);
    }

    limit = pow(2, timer_bits);

    logInfo("\n***********************************************************\n");
    printf(" Timer (Sec) = %.2f \n", timer);
    printf(" Timer Frequcny (Hz): %.0f \n", timer_freq);
    printf(" Number of timer bits (16 or 32): %d \n", timer_bits);
    logInfo("***********************************************************\n");

    for (prescaler = 0; prescaler < 65536; prescaler++)
    {
        cnt_clk = (timer_freq / (prescaler + 1));
        time_period = 1 / cnt_clk;
        period_value = timer / time_period;

        if (period_value < limit)
        {
            // printf("Count Clock = %.0f \n", cnt_clk);
            printf("\033[0;32m"); /*Green Color*/
            printf("\n ARR Register - 1 = %.0f \n", period_value - 1);
            printf(" Prescaler = %d \n \n", prescaler);
            return 0;
        }
    }
    logError("Not Found!");

    return 0;
}