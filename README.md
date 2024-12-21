
<!-- README.md is generated from README.Rmd. Please edit that file -->

# itmsa

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-cyan.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![CRAN](https://www.r-pkg.org/badges/version/itmsa)](https://CRAN.R-project.org/package=itmsa)
[![DownloadsAll](https://badgen.net/cran/dt/itmsa?color=orange)](https://CRAN.R-project.org/package=itmsa)
[![DownloadsMonth](https://cranlogs.r-pkg.org/badges/itmsa)](https://CRAN.R-project.org/package=itmsa)
[![R-universe](https://stscl.r-universe.dev/badges/itmsa?color=cyan)](https://stscl.r-universe.dev/itmsa)
<!-- badges: end -->

**Information-Theoretic Measures for Spatial Association**

## Installation

- Install from [CRAN](https://CRAN.R-project.org/package=itmsa) with:

``` r
install.packages("itmsa", dep = TRUE)
```

- Install binary version from
  [R-universe](https://stscl.r-universe.dev/sshicm) with:

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
