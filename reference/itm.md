# Information-Theoretic Measures for Spatial Association

Information-Theoretic Measures for Spatial Association

## Usage

``` r
itm(
  formula,
  data,
  method = c("vm", "icm"),
  beta = 1,
  unit = c("e", "2", "10"),
  seed = 42,
  permutation_number = 999
)
```

## Arguments

- formula:

  A formula.

- data:

  A `data.frame`, `tibble` or `sf` object of observation data.

- method:

  (optional) whether `vm`(default) or `icm`.

- beta:

  (optional) The \\\beta\\ value used fo `vm` measure, default is `1`.

- unit:

  (optional) Logarithm base, default is `e`.

- seed:

  (optional) Random number seed, default is `42`.

- permutation_number:

  (optional) Number of Random Permutations, default is `999`.

## Value

A `tibble`.

## Examples

``` r
sim = readr::read_csv(system.file('extdata/sim.csv',package = 'itmsa'))
#> Rows: 80 Columns: 4
#> ── Column specification ────────────────────────────────────────────────────────
#> Delimiter: ","
#> dbl (4): z1, z2, x, y
#> 
#> ℹ Use `spec()` to retrieve the full column specification for this data.
#> ℹ Specify the column types or set `show_col_types = FALSE` to quiet this message.
# \donttest{
# Information-theoretical V-measure
itm(z1 ~ z2, data = sim, method = 'vm')
#> # A tibble: 1 × 3
#>   Variable    Iv    Pv
#>   <chr>    <dbl> <dbl>
#> 1 z2       0.361     0
# Information Consistency-Based Measures
itm(z1 ~ z2, data = sim, method = 'icm')
#> # A tibble: 1 × 3
#>   Variable    Iv    Pv
#>   <chr>    <dbl> <dbl>
#> 1 z2       0.315     0
# }
```
