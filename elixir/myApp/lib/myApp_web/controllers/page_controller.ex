defmodule MyAppWeb.PageController do
  use MyAppWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end

  def studentNumber(conn, _params) do
    changeset = %{}
    render conn, "studentnumber.html"
  end

  def create(conn, %{"studentNumber" => studentNumber} = params) do

    valid = String.match?(studentNumber, ~r/^[sS]?\d{7}/)

    if valid do
      checkSum = studentNumber
      |> String.replace(~r/^[sS]?/, "")
      |> String.to_integer
      |> Integer.digits
      |> Enum.sum
      render conn, "studentnumber.html", message: "De checksum van uw studentnummer is: #{checkSum}"
    else
      render conn, "studentnumber.html", message: "Het studentnummer moet beginnen met een 's' en 7 cijfers bevatten"
    end
  end
end
