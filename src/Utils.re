[@bs.module] external drizzle: string = "./images/drizzle.png";
[@bs.module] external heavyRain: string = "./images/heavy-rain.png";
[@bs.module] external heavySnow: string = "./images/heavy-snow.png";
[@bs.module] external lightning: string = "./images/lightning.png";
[@bs.module] external moon: string = "./images/moon.png";
[@bs.module]
external partlyCloudyMoon: string = "./images/partly-cloudy-moon.png";
[@bs.module] external partlySunny: string = "./images/partly-sunny.png";
[@bs.module] external sunny: string = "./images/sunny.png";
[@bs.module] external thermometer: string = "./images/thermometer.png";

let roundedStringOfFloat = num => num |> floor |> truncate |> Js.Int.toString;

let getImage = code =>
  switch (code) {
  | "01d" => sunny
  | "01n" => moon
  | "02d"
  | "03d"
  | "04d" => partlySunny
  | "02n"
  | "03n"
  | "04n" => partlyCloudyMoon
  | "10d" => drizzle
  | "09d" => heavyRain
  | "13d" => heavySnow
  | "11d" => lightning
  | _ => thermometer
  };