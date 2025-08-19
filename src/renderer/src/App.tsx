import TitleBar from "./components/TitleBar"
import ToolBar from "./components/ToolBar"
import React from "react"
import "./assets/main.css"

function App(): React.JSX.Element {
  return (
    <>
      <TitleBar />
      <ToolBar />
    </>
  )
}

export default App
