#' Information-Theoretic Measures for Spatial Association
#'
#' @param formula A formula.
#' @param data A `data.frame`, `tibble` or `sf` object of observation data.
#' @param method (optional) whether `vm`(default) or `icm`.
#' @param beta (optional) The \eqn{\beta} value used fo `vm` measure, default is `1`.
#' @param unit (optional) Logarithm base, default is `e`.
#' @param seed (optional) Random number seed, default is `42`.
#' @param permutation_number (optional) Number of Random Permutations, default is `999`.
#'
#' @return A `tibble`.
#' @export
#'
#' @examples
#' sim = readr::read_csv(system.file('extdata/sim.csv',package = 'itmsa'))
#' \donttest{
#' # Information-theoretical V-measure
#' itm(z1 ~ z2, data = sim, method = 'vm')
#' # Information Consistency-Based Measures
#' itm(z1 ~ z2, data = sim, method = 'icm')
#' }
itm = \(formula, data, method = c("vm","icm"), beta = 1,
        unit = c("e","2","10"), seed = 42, permutation_number = 999){
  if (inherits(data,"sf")){
    data = sf::st_drop_geometry(data)
  }
  data = sdsfun::tbl_all2int(data)
  formulavar = sdsfun::formula_varname(formula,data)
  yvec = data[,formulavar[[1]],drop = TRUE]
  xtbl = dplyr::select(data,dplyr::all_of(formulavar[[2]]))

  unit = match.arg(unit)
  method = match.arg(method)
  res = purrr::map_dfr(xtbl,
                       \(.x) {
                         if (method == "icm") {
                           return(RcppICMP(yvec, .x, unit, seed,
                                           permutation_number))
                         } else {
                           return(RcppVMP(yvec,.x,unit,beta,seed,
                                          permutation_number))
                         }
                       }) |>
    dplyr::mutate(Variable = names(xtbl)) |>
    dplyr::select(Variable,Iv,Pv) |>
    dplyr::arrange(dplyr::desc(Iv))
  return(res)
}
