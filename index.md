# itmsa

logo by Sibyl

**Information-Theoretic Measures for Spatial Association**

## Installation

- Install from [CRAN](https://CRAN.R-project.org/package=itmsa) with:

``` r
install.packages("itmsa", dep = TRUE)
```

- Install binary version from
  [R-universe](https://stscl.r-universe.dev/itmsa) with:

``` r
install.packages("itmsa",
                 repos = c("https://stscl.r-universe.dev",
                           "https://cloud.r-project.org"),
                 dep = TRUE)
```

- Install from source code on [GitHub](https://github.com/stscl/itmsa)
  with:

``` r
if (!requireNamespace("devtools")) {
    install.packages("devtools")
}
devtools::install_github("stscl/itmsa",
                         build_vignettes = TRUE,
                         dep = TRUE)
```
