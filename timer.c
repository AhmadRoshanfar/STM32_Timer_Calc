#include <stdio.h>
#include <math.h>

int main()
{
    int timer_ms = 0;
    double timer = 0;
    int timer_freq_MHz = 0;
    double timer_freq = 0;
    int timer_bits = 0;
    double cnt_clk = 0;
    int prescaler = 0;
    double time_period;
    double period_value;
    double limit = 0;

    printf("\n Timer(ms): ");
    scanf("%d", &timer_ms);
    timer = timer_ms * pow(10, -3);

    printf(" Timer Frequcny(MHz): ");
    scanf("%d", &timer_freq_MHz);
    timer_freq = (timer_freq_MHz * pow(10, 6));

    printf(" Number of timer bits (16 or 32): ");
    scanf("%d", &timer_bits);
    while (!(timer_bits != 16 ^ timer_bits != 32))
    {
        printf("\033[0;31m");
        printf(" Number of timer bits must be 16 or 32 bits\n");
        printf("\033[0m");
        printf(" Number of timer bits (16 or 32): ");
        scanf("%d", &timer_bits);
    }

    limit = pow(2, timer_bits);

    printf("\n***********************\n");
    printf(" Timer (Sec) = %.2f \n", timer);
    printf(" Timer Frequcny (Hz): %.0f \n", timer_freq);
    printf(" Number of timer bits (16 or 32): %d \n", timer_bits);
    printf("***********************\n");

    for (prescaler = 0; prescaler < 65536; prescaler++)
    {
        cnt_clk = (timer_freq / (prescaler + 1));
        time_period = 1 / cnt_clk;
        period_value = timer / time_period;

        if (period_value < limit)
        {
            // printf("Count Clock = %.0f \n", cnt_clk);
            printf("\033[0;32m");
            printf("\n ARR Register - 1 = %.0f \n", period_value - 1);
            printf(" Prescaler = %d \n \n", prescaler);
            return 0;
        }
    }

    return 0;
}