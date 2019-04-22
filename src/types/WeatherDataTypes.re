/* ================== DECODED RESPONSE TYPES ================== */
type decodedCurrentWeather = {
  current: float,
  tempMin: float,
  tempMax: float,
};

type decodedForecastWeatherItem = {
  icon: string,
  description: string,
};

type decodedTempType = {
  min: float,
  max: float,
};

type decodedForecastData = {
  dt: int,
  weather: list(decodedForecastWeatherItem),
  temp: decodedTempType,
};

type decodedForecast = {list: list(decodedForecastData)};

type transformedForecastItem = {
  icon: string,
  description: string,
  temp: decodedTempType,
  dt: int,
};

type transformedForecast = list(transformedForecastItem);