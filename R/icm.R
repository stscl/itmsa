#' Information Consistency-Based Measures for Spatial Association
#'
#' @param formula A formula.
#' @param data A `data.frame`, `tibble` or `sf` object of observation data.
#' @param unit (optional) Logarithm base, default is `e`.
#' @param seed (optional) Random number seed, default is `42`.
#' @param permutation_number (optional) Number of Random Permutations, default is `999`.
#'
#' @return A `tibble`.
#' @export
#'
#' @examples
#' d = c(rep(1,7),rep(2,3),rep(1,3),rep(2,7))
#' s = rep(1:2, each = 10)
#' demodf = data.frame(d = d, s = s)
#' icm(d ~ s, data = demodf)
#'
icm = \(formula, data, unit = c("e","2","10"),
        seed = 42, permutation_number = 999){
  if (inherits(data,"sf")){
    data = sf::st_drop_geometry(data)
  }
  data = sdsfun::tbl_all2int(data)
  formulavar = sdsfun::formula_varname(formula,data)
  yvec = data[,formulavar[[1]],drop = TRUE]
  xtbl = dplyr::select(data,dplyr::all_of(formulavar[[2]]))

  unit = match.arg(unit)
  res = purrr::map_dfr(xtbl,
                       \(.x) RcppICMP(yvec,.x, unit, seed,
                                      permutation_number)) |>
    dplyr::mutate(Variable = names(xtbl)) |>
    dplyr::select(Variable,Ic,Pv) |>
    dplyr::arrange(dplyr::desc(Ic))
  return(res)
}
