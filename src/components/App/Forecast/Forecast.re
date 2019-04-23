[%bs.raw {|require('./Forecast.scss')|}];

let formattedDate = dateInt => {
  let fixedDate = string_of_int(dateInt) ++ "000" |> float_of_string;
  MomentRe.momentWithTimestampMS(fixedDate)
  |> MomentRe.Moment.format("dddd, MMM D");
};

[@react.component]
let make = (~forecast) =>
  switch (forecast) {
  | None => ReasonReact.null
  | Some(f) =>
    <div className="container">
      {
        f
        |> List.map((item: WeatherDataTypes.transformedForecastItem) => {
             let icon: string = Utils.getImage(item.icon);
             <div
               className="weather-item-container"
               key={string_of_int(item.dt)}>
               <div className="weather-item-inner-container">
                 <div>
                   <h3 className="date-heading">
                     {formattedDate(item.dt) |> ReasonReact.string}
                   </h3>
                   <p className="weather-description">
                     {
                       item.description
                       |> String.capitalize
                       |> ReasonReact.string
                     }
                   </p>
                 </div>
               </div>
               <div className="temp-and-img-container">
                 <img className="weather-img" alt="" src=icon />
                 <div className="temp-min-max-container">
                   <p className="temp-min-max-text">
                     {
                       Utils.roundedStringOfFloat(item.temp.max)
                       |> ReasonReact.string
                     }
                   </p>
                   <p className="temp-min-max-text">
                     {
                       Utils.roundedStringOfFloat(item.temp.max)
                       |> ReasonReact.string
                     }
                   </p>
                 </div>
               </div>
             </div>;
           })
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>
  };