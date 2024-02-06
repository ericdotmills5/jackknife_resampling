from itertools import combinations
from scipy.optimize import minimize
import pandas as pd

n = 18 # number of subjects
T = 72 # number of trials
d = 2 # how many to delete
q = 0.5 # q
combos = list(combinations(range(0, n), d)) # all combinations of n choose d
file_name = "place_csv_here/test_data_large_18x72.csv" 


# data = nxTx2 3d tensor; rows = subjects; columns = trial no.; depth 0 = mu, depth 1 = skill

# define objective function to optimise, use kwargs to put alpha, beta in
def obj(x, to_delete):
    alpha = x[0]
    beta = x[1]
    sumZ = 0

    for i in range(0, n):
        if i in to_delete:
            continue
        
        for j in range(0, T):
            y_i = data[i][j][1]
            x_i = data[i][j][0]
            indicator = 1 if (y_i <= alpha + beta * x_i) else 0

            sumZ += (q - indicator) * (y_i - alpha - beta * x_i)

    return sumZ

# extract data
df = pd.read_csv(file_name)
data = [[] for _ in range(n)]

# assume csv is in correct form
for i in range(0, df.shape[0]): # for each row in the csv
    subj = i % n # assume rows after n are retrials
    to_append = (df.iloc[i, 1], df.iloc[i, 2]) # insert [x, y] as tuple
    data[subj].append(to_append)
'''
data tensor form:
    rows = subjects
    columns = trials
    depth[0] = x, depth[1] = y
'''

sum_alpha = 0
sum_beta = 0
for i in combos:
    to_delete = i
    
    x_init = [0, 0]
    alpha, beta = minimize(obj, x_init, args=(to_delete,), method="SLSQP").x
    
    sum_alpha += alpha
    sum_beta += beta
print(sum_alpha, sum_beta)

'''
to do:
    implement into c
        how will you import the csv data?
    
'''