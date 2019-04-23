[%bs.raw {|require('./app.scss')|}];
/* [@bs.module] external logo: string = "../../images/logo.svg"; */

[@react.component]
let make = _ => {
  let (selectedCity, updateSelectedCity) = React.useState(() => "seattle");
  let (currentWeather, updateCurrentWeather) = React.useState(() => None);
  let (forecast, updateForecast) = React.useState(() => None);

  let handleCitySelected = city => updateSelectedCity(_ => city);

  React.useEffect1(
    () => {
      let _ =
        WeatherDataFetchers.fetchCurrentWeather(selectedCity, data =>
          updateCurrentWeather(_ => Some(data))
        );

      let _ =
        WeatherDataFetchers.fetchForecast(selectedCity, data =>
          updateForecast(_ => Some(data))
        );

      None;
    },
    [|selectedCity|],
  );

  <div className="App">
    <CurrentWeather
      currentWeatherData=currentWeather
      selectedCity
      onChangeCity=handleCitySelected
    />
    <Forecast forecast />
  </div>;
};