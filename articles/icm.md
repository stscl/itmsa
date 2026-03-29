# Information Consistency-Based Measures for Spatial Association

## 1. The principle of the information consistency-based measures

\\ I\_{N}\left(d,s\right) = \frac{I \left(d,s\right)}{I \left(d\right)}
= \frac{I \left(d\right) - I \left(d \mid s\right)}{I \left(d\right)} =
1 - \frac{\sum\_{s_i \in S}\sum\_{x \in V_d} p\left(s_i,x\right) \log
p\left(x \mid s_i\right)}{\sum\_{x \in V_d} p\left(x\right) \log
p\left(x\right)} \\

where \\p\left(x\right)\\ is the probability of observing \\x\\ in
\\U\\, \\p\left(s_i,x\right)\\ is the probability of observing \\s_i\\
and \\x\\ in \\U\\, and \\p\left(x \mid s_i\right)\\ is the probability
of observing \\x\\ given that the stratum is \\s_i\\.

## 2. Example

``` r
install.packages("itmsa", dep = TRUE)
install.packages("gdverse", dep = TRUE)
```

``` r
library(itmsa)
```

``` r
ntds = gdverse::NTDs
ntds$incidence = sdsfun::discretize_vector(ntds$incidence, 5)
itm(incidence ~ watershed + elevation + soiltype,
    data = ntds, method = "icm")
## # A tibble: 3 × 3
##   Variable     Iv    Pv
##   <chr>     <dbl> <dbl>
## 1 watershed 0.445     0
## 2 elevation 0.390     0
## 3 soiltype  0.210     0
```
