let useInterval = (callback, delay) => {
  let savedCallback = React.useRef(callback);

  React.useEffect(() => {
    React.Ref.setCurrent(savedCallback, callback);
    None;
  });

  React.useEffect0(() => {
    let timerId =
      Js.Global.setInterval(React.Ref.current(savedCallback), delay);
    Some(() => Js.Global.clearInterval(timerId));
  });
};

let getFormattedDate = () =>
  MomentRe.momentNow() |> MomentRe.Moment.format("MMMM D, h:mm a");

let useUpdatingFormattedDate = interval => {
  let (date, updateDate) = React.useState(getFormattedDate);
  useInterval(
    () => {
      let newDate = getFormattedDate();
      if (newDate != date) {
        updateDate(_ => newDate);
      };
    },
    interval,
  );
  date;
};