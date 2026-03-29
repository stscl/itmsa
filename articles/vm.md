# Information-theoretical V-measure for Spatial Association

## 1. The principle of the information-theoretical V-measure

Let us denote the area of the domain as A. Consider two different
regionalizations of the domain. To make a further discussion more lucid,
we will refer to the first one as a regionalization and to the second
one as a partition. The regionalization \\R\\ divides the domain into
\\n\\ regions \\r_i \mid i = 1,\ldots,n\\. The partition \\Z\\ divides
the domain into \\m\\ zones \\z_j \mid j = 1,\ldots,n\\. Both \\R\\ and
\\Z\\ are essentially integer-type vectors with equal elements.

\\ h = 1 - \sum\limits\_{j=1}^m \frac{A_j}{A} \frac{S_j^R}{S^R} \\

where \\S^R = - \sum\limits\_{i=1}^n \frac{A_i}{A} \log\frac{A_i}{A}\\,
\\S_j^R = - \sum\limits\_{i=1}^n \frac{a\_{i,j}}{A_j} \log
\frac{a\_{i,j}}{A_j}\\, and \\a\_{i,j}\\ represents the count of
elements where \\R==i\\ and \\Z==j\\. \\A_i\\ is the number of elements
in the vector where \\R==i\\, and \\A_j\\ is the number of elements in
the vector where \\Z==j\\.

By swapping \\R\\ and \\Z\\, \\c\\ can be calculated. Finally, the
v-measure can be calculated useing the below formula:

\\ V\_{\beta} = \frac{(1+\beta)hc}{(\beta h) + c} \\

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
    data = ntds, method = "vm")
## # A tibble: 3 × 3
##   Variable     Iv    Pv
##   <chr>     <dbl> <dbl>
## 1 watershed 0.373     0
## 2 elevation 0.365     0
## 3 soiltype  0.213     0
```
