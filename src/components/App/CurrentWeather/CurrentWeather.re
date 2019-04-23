[%bs.raw {|require('./CurrentWeather.scss')|}];

[@react.component]
let make = (~onChangeCity, ~currentWeatherData, ~selectedCity) => {
  let (cityText, updateCityText) = React.useState(() => "seattle");
  let date = Hooks.useUpdatingFormattedDate(10000);

  let handleClick = _ => {
    let _ = onChangeCity(cityText);
    updateCityText(_ => "");
  };

  let handleChange = e =>
    ReactEvent.Form.target(e)##value |> updateCityText(_);

  <header className="current-weather-container">
    <div>
      <p className="current-time-text"> {ReasonReact.string(date)} </p>
      {
        switch (
          (currentWeatherData: option(WeatherDataTypes.decodedCurrentWeather))
        ) {
        | Some(d) =>
          let max = Utils.roundedStringOfFloat(d.tempMax);
          let min = Utils.roundedStringOfFloat(d.tempMin);
          let current = Utils.roundedStringOfFloat(d.current);
          let minMaxString = {j|Max $maxº | Min $minº|j};
          let currentTempString = {j|$currentº|j};

          <React.Fragment>
            <p className="min-max-text">
              {ReasonReact.string(minMaxString)}
            </p>
            <h1 className="current-temp-text">
              {ReasonReact.string(currentTempString)}
            </h1>
          </React.Fragment>;
        | None => ReasonReact.null
        }
      }
    </div>
    <div className="city-container">
      <h1> {selectedCity |> String.capitalize |> ReasonReact.string} </h1>
      <input
        type_="Text"
        placeholder="Enter City"
        value=cityText
        onChange=handleChange
      />
      <button onClick=handleClick> {ReasonReact.string("Submit")} </button>
    </div>
  </header>;
};