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
