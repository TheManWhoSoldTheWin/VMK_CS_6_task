#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

extern double df1(double x);
extern double df2(double x);
extern double df3(double x);

static int help = 0;
static int point = 0;
static int itter = 0;
static int option = 0;
//extern double diff(double (*f)(double), double x);
// Для тестового запуска ищем производную функции в точке
/*
double diff (double (*f)(double), double x) {
    double h = 0.00001;
    return (f(x + h) - f(x)) / h;
}*/
double root (double (*f)(double), double (*g)(double), double a, double b, double eps1, double (*diff_f)(double), double (*diff_g)(double)) {
    int itteration = 0;
    double x = (a + b) / 2;
    double f_x = f(x) - g(x); // значение функции в середине отрезка
    double middle = (f(a) - g(a) + f(b) - g(b)) / 2;
    if (f_x < middle){  // выпукла вниз => x = b
        x = b;
    } else {
        x = a;
    }
    eps1 /= 2;
    while (1){
        if ( ((f(x - eps1) - g(x - eps1)) * (f(x + eps1) - g(x + eps1))) <= 0){// точность эпсилон
            break;
        }
        itteration++;
        double z = x - (f(x) - g(x)) / (diff_f(x) - diff_g(x));
        if (option == 1)
            printf("Next step in find root %f\n", z);
        x = z;// заново заполняем следущую

    }
    if (option || point){
        printf("  Root is %f \n", x);
    }
    if (itter || option)
        printf("For find root need %d step\n", itteration);
    return x; // нашли точку которая подходит под заданный eps1
}
double integral_true (double (*f)(double), double a, double b, double eps2){
    int n = 1; // разбиение отрезка на n -частей
    eps2 /= 3;
    int step = 0;
    double h = fabs((b - a) / n);
    double I = 0;
    double In = (f(a) / 2 + f(b)/ 2);// Храним значения функции БЕЗ высоты трапеции
    double Ih = h * In;
    // Когда разница между соседними посчитанными интегралами меньше eps2 заканчиваем
    while (fabs(I - Ih) > (eps2 / 3)) {  // точность в правиле рунге
        I = Ih;
        n *= 2;
        step ++;
        double h = fabs((b - a) / n); //высота трапеции при новом разбиение
        for (int i = 1; i < n; i += 2) {
            In += f(a + i * h);
        }
        Ih = h * In;
        if (option) {
            printf("Find integral summ is %f\n", Ih);
        }
    }
    if (option || point){
        printf(" Integral is %f \n", Ih);
    }
    if (itter || option) {
        printf("For find integral need %d step\n", step);
    }
    return Ih;
}

int main(void)
{
    char a[10];
    while(1){
        char c = getchar();
        if (c != '-')
            break;

        fgets(a, 10, stdin);
        if (!strcmp(a, "help\n")){
            help = 1;
        }
        if (!strcmp(a, "p\n")){ //p -point
            point = 1;
        }
        if (!strcmp(a, "i\n")){ // i -iteration
            itter = 1;
        }
        if (!strcmp(a, "o\n")){ // o -options
            option = 1;
        }
    }
    double eps1 = 0.0001;
    double eps2 = 0.001;
    if (help == 1){
        printf("-p - shows the intersection points of the curves\n");
        printf("-i - outputs the number of iterations to find the root\n");
        printf("-o - show the information of program\n");
    }
    printf("\n");
    printf("Solve the task 4\n");
    printf("First function is y1 = e^x + 2\n");
    printf("Second function is y2 = -1/x\n");
    printf("Third function is y3 = -2(x+1)/3\n");
    printf("\n");
    printf("For function use lexicographic order!\n");
    printf("\n");
    double root_12 = root(f1, f2, -10, -0.2, eps1, df1, df2); // [-10;-0.2]
    double root_13= root(f1, f3, -4.2, -3.7, eps1, df1, df3); // [-4.2;-3.7]
    double root_23 = root(f2, f3, -2, -1, eps1, df2, df3); // [-2;-1]

    double integral_1 = integral_true(f1, root_13, root_12, eps2);
    double integral_2 = integral_true(f2, root_23, root_12, eps2);
    double integral_3 = integral_true(f3, root_13, root_23, eps2);/*
    if (point == 1){
        printf("Point of cross 1 and 2 function is %f\n", root_12);
        printf("Point of cross 1 and 3 function is %f\n", root_13);
        printf("Point of cross 2 and 3 function is %f\n", root_23);
        printf("Integral of function 2 is %f\n", integral_2);
        printf("Integral of function 1 is %f\n", integral_1);
        printf("Integral of function 3 is %f\n", integral_3);
        printf("\n");
        printf("Final integral?\n");
        double answer = fabs(integral_1 - integral_2 - integral_3);
        printf("%f\n", answer);
    }
    if (itter == 1){

        double integral_2 = integral_true(f2, root_23, root_12, eps2);

        double integral_1 = integral_true(f1, root_13, root_12, eps2);

        double integral_3 = integral_true(f3, root_13, root_23, eps2);
    }*/
    if (option) {
        double answer = fabs(integral_1 - integral_2 - integral_3);
        printf("%Final answer of integral f\n", answer);
    }
    getchar();
    return 0;
}
