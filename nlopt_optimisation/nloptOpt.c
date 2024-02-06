#include <nlopt.h>
#include <stdio.h>

typedef struct {
    double a, b;
} TestParams;

typedef struct {
    double x, y, minf;
} OptimisedOutputs;

typedef double (*ObjFunc)(unsigned, const double*, double*, void*);

double testObj(unsigned n, const double *x, double *grad, void *params) {
    TestParams *p = (TestParams *) params;
    double a = p->a, b = p->b;

    return (x[0] - a)*(x[0] - b) + x[1] * x[1];
} // assume gradient isnt needed, since using derivtive free minimisation

OptimisedOutputs optimise(ObjFunc obj, void *params) {
    nlopt_opt opt; // optimisation struct
    opt = nlopt_create(NLOPT_LN_NELDERMEAD, 2); // use neldermead algo with 2 variables
    nlopt_set_min_objective(opt, obj, params); // declare objective function with params

    double x[2] = {0, 0};  // arbitrary initial guess
    double minf; // declare minimised function output

    nlopt_result result = nlopt_optimize(opt, x, &minf); // run algorithm

    if (result < 0) {
        printf("nlopt failed!\n");
    }

    OptimisedOutputs toReturn = {x[0], x[1], minf};
    nlopt_destroy(opt); // free memory
    return toReturn;
}

int main() {
    TestParams params = {5, 7}; // declare constant parameters
    
    OptimisedOutputs out = optimise(testObj, &params);

    printf("found minimum at f(%g,%g) = %0.10g\n", out.x, out.y, out.minf);

    return 0;
}
// compile with gcc -o nloptOpt.out nloptOpt.c -lnlopt