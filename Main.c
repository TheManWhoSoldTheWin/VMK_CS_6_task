#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
typedef double (*func_t) (double);
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

extern double df1(double x);
extern double df2(double x);
extern double df3(double x);
// f1 = -5
double test_f1(double x) {
    return -5;
}
// f2 = -x + 5
double test_f2(double x) {
    return -x + 5;
}
// f3 = x + 5
double test_f3(double x) {
    return x + 5;
}
// df1 = 0
double test_df1(double x) {
    return 0;
}
// df2 = -1
double test_df2(double x) {
    return -1;
}
// df3 = 1
double test_df3(double x) {
    return 1;
}
static int help = 0;
static int point = 0;
static int itter = 0;
static int option = 0;
static int test = 0; // Flag for check functiondouble *diff1 = df1;

double root (func_t f, func_t g, double a, double b, double eps1, func_t diff_f, func_t diff_g) {
    int itteration = 0;
    double x = (a + b) / 2;
    double f_x = f(x) - g(x); // the value of the function in the middle of the segment
    double middle = (f(a) - g(a) + f(b) - g(b)) / 2;
    if (f_x < middle){  // convex downwards => x = b
        x = b;
    } else {
        x = a;
    }
    eps1 /= 2;
    while (1){
        if ( ((f(x - eps1) - g(x - eps1)) * (f(x + eps1) - g(x + eps1))) <= 0){
            break;
        }
        itteration++;
        double z = x - (f(x) - g(x)) / (diff_f(x) - diff_g(x));
        if (option == 1)
            printf("Next step in find root %f\n", z);
        x = z;// fill in the next one again

    }
    if (option || point){
        printf("  Root is %f \n", x);
    }
    if (itter || option)
        printf("For find root need %d step\n", itteration);
    return x; // found a point that fits the given eps1
}
double integral_true (func_t f, double a, double b, double eps2){
    int n = 1; // division of a segment into n-parts
    eps2 /= 3;
    int step = 0;
    double h = fabs((b - a) / n);
    double I = 0;
    double In = (f(a) / 2 + f(b)/ 2);// Store the function values ​​WITHOUT the height of the trapezoid
    double Ih = h * In;
    // When the difference between adjacent calculated integrals is less than eps2 we finish
    while (fabs(I - Ih) > (eps2 / 3)) {
        I = Ih;
        n *= 2;
        step ++;
        double h = fabs((b - a) / n); //height of the trapezoid for the new division double * diff1 = df1;
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

int main(int argc, char **argv)
{
    for (int flag = 0; flag < argc; flag ++ ) {
        test |= (strcmp(argv[flag], "-test") == 0);// if we get flag of test we put in test = 1;
        point |= (strcmp(argv[flag], "-p") == 0);
        itter |= (strcmp(argv[flag], "-i") == 0);
        option |= (strcmp(argv[flag], "-o") == 0);
        help |= (strcmp(argv[flag], "-help") == 0);
    }
    double eps1 = 0.0001;
    double eps2 = 0.001;
    if (help == 1){
        printf("-test - check function in NOT MAIN variation (get eaxmple function)\n");
        printf("-p - shows the intersection points of the curves\n");
        printf("-i - outputs the number of iterations to find the root\n");
        printf("-o - show the information of program\n");
    }
    printf("\n");
    if (!test){
        printf("Solve the task 4\n");
        printf("First function is y1 = e^x + 2\n");
        printf("Second function is y2 = -1/x\n");
        printf("Third function is y3 = -2(x+1)/3\n");
        printf("\n");
        printf("For function use lexicographic order!\n");
        printf("\n");
    } else {
        printf("Solve the task 4 example test\n");
        printf("First function is y1 = -5\n");
        printf("Second function is y2 = -x + 5\n");
        printf("Third function is y3 = x + 5\n");
        printf("\n");
        printf("For function use lexicographic order!\n");
        printf("\n");

    }

    // We choose mode for function in task
    //This is main task
    func_t diff1 = df1;
    func_t diff2 = df2;
    func_t diff3 = df3;
    func_t choose_f1 = f1;
    func_t choose_f2 = f2;
    func_t choose_f3 = f3;
    // set [;] when we find root for main function
    double a1 = -10, a2 = -0.2; //for function 1 and 2
    double b1 = -4.2, b2 = -3.7; // for function 1 and 3
    double c1 = -2, c2 = -1; // for function 2 and 3
    if (test == 1){
        // This is check task
        diff1 = test_df1;
        diff2 = test_df2;
        diff3 = test_df3;
        choose_f1 = test_f1;
        choose_f2 = test_f2;
        choose_f3 = test_f3;
        a1 = -20, a2 = 20;
        b1 = -20, b2 = 20;
        c1 = -20, c2 = 20;
    }
    double root_12 = root(choose_f1, choose_f2, a1, a2, eps1, diff1, diff2);
    double root_13= root(choose_f1, choose_f3, b1, b2, eps1, diff1, diff3);
    double root_23 = root(choose_f2, choose_f3, c1, c2, eps1, diff2, diff3);

    double integral_1 = integral_true(choose_f1, root_13, root_12, eps2);
    double integral_2 = integral_true(choose_f2, root_23, root_12, eps2);
    double integral_3 = integral_true(choose_f3, root_13, root_23, eps2);

    if (option) {
        double answer = fabs(integral_1 - integral_2 - integral_3);
        printf("Final answer of integral %f\n", answer);
    }
    getchar();
    return 0;
}
