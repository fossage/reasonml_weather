open WeatherDataTypes;

module Decode = {
  let main = json =>
    Json.{
      current: json |> Decode.field("temp", Decode.float),
      tempMin: json |> Decode.field("temp_min", Decode.float),
      tempMax: json |> Decode.field("temp_max", Decode.float),
    };

  let current = json => Json.Decode.(json |> field("main", main));

  let weatherItem = json =>
    Json.Decode.{
      icon: json |> field("icon", string),
      description: json |> field("description", string),
    };

  let temp = json =>
    Json.{
      min: json |> Decode.field("min", Decode.float),
      max: json |> Decode.field("max", Decode.float),
    };

  let forecastList = json =>
    Json.{
      dt: json |> Decode.field("dt", Decode.int),
      weather: json |> Decode.field("weather", Decode.list(weatherItem)),
      temp: json |> Decode.field("temp", temp),
    };

  let forecast = json =>
    Json.Decode.{list: json |> field("list", list(forecastList))};
};

let rootUrl = "https://api.openweathermap.org/data/2.5/";

let assembleUrl = (requestType, location) =>
  rootUrl
  ++ requestType
  ++ "?q="
  ++ location
  ++ "&mode=json&appid=c36043dd046f0d256302ccfa30d8c6ad&units=imperial";

let fetchData = (url, decoder, callback) =>
  Js.Promise.(
    url
    |> Fetch.fetch
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> decoder
         |> (
           data => {
             callback(data);
             resolve();
           }
         )
       )
  );

let transformForecast = (forecast: decodedForecast) =>
  forecast.list
  |> List.map(forecastItem => {
       let weather = List.nth(forecastItem.weather, 0);

       {
         icon: weather.icon,
         description: weather.description,
         temp: forecastItem.temp,
         dt: forecastItem.dt,
       };
     });

let fetchForecast = (location, callback) =>
  assembleUrl("forecast/daily", location)
  ->(
      fetchData(Decode.forecast, response =>
        transformForecast(response) |> callback
      )
    );

let fetchCurrentWeather = (location, callback) =>
  assembleUrl("weather", location)->(fetchData(Decode.current, callback));