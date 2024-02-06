#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>

const double PRECISION = 1e-3; // 3 decimal places

typedef struct {
    double coeff;
} Parameters;

double obj(const gsl_vector* v, void* params) {
    double x, y;

    x = gsl_vector_get(v, 0);
    y = gsl_vector_get(v, 1);
    Parameters* p = (Parameters*)params;
    return (x - p->coeff) * (x - 1) + y * y;
}

int main() {
    // declare minimisation algorithm to use
    const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2; 
    gsl_multimin_fminimizer *s = NULL; // declare state of minimisation
    gsl_vector *ss, *x; // declare step size, and initial guess
    gsl_multimin_function minStruct; // declare the multimin structure holding func, and params

    // declare loop variables
    size_t iter = 0;
    int status;
    double size;

    // define arbitrary starting point <0, 0>
    x = gsl_vector_alloc(2);
    gsl_vector_set(x, 0, 0);
    gsl_vector_set(x, 1, 0);

    // initialise step size
    ss = gsl_vector_alloc(2);
    gsl_vector_set_all(ss, 0.1);

    // initialise parameters
    Parameters params = {2.2};

    // initialise multimin structure
    minStruct.n = 2;
    minStruct.f = obj;
    minStruct.params = &params;

    s = gsl_multimin_fminimizer_alloc(T, 2);
    gsl_multimin_fminimizer_set(s, &minStruct, x, ss);

    do {
        iter++;
        status = gsl_multimin_fminimizer_iterate(s); // update status of new point

        if (status){ // if status is non zero, an error has occured
            printf("Non-zero return status");
            break;
        }

        size = gsl_multimin_fminimizer_size(s);
        status = gsl_multimin_test_size(size, PRECISION);

        if (status == GSL_SUCCESS) {
            printf("converged to minimum at\n");
        }

        printf("%5ld %.5f %.5f f() = %7.3f size = %.3f\n", iter,
            gsl_vector_get(s->x, 0), 
            gsl_vector_get(s->x, 1), 
            s->fval, size);
    } while (status == GSL_CONTINUE && iter < 1000);
    
    // free memory
    gsl_vector_free(x);
    gsl_vector_free(ss);
    gsl_multimin_fminimizer_free(s);

    return 0;
}
// this doesnt actually converge to the correct minima and i don't know why :/


