# Project Description
Given a data set (<3000 entries), the program will fit a quantile regression model by estimating the alpha and beta parameters. The program will do this by finding the 1st-4th moments of the estimated parameters through Jackknife Resampling, and calculating relavent statistics using these moments.

This project is to be implemented with C++ (and python as a draft). 

Currently, in python, the running time fluctuates based on the number of elements one wishes to delete, taking 10 seconds for d = 1 and 20 hours for d = n/2.