import { JSX } from "react"
import { Splitter } from "antd"
import TitleBar from "./components/TitleBar"
import ToolBar from "./components/ToolBar"
import MyLibrary from "./pages/MyLibrary"
import "./assets/main.css"

export default function App(): JSX.Element {
  return (
    <>
      <TitleBar />
      <ToolBar />
      <Splitter className="main-panel-container">
        <Splitter.Panel className="side-panel" defaultSize="30%" min="25%" max="30%">
          <div className="side-panel-content">
            [Work in progress...]
          </div>
        </Splitter.Panel>

        <Splitter.Panel className="content-panel">
          <MyLibrary />
        </Splitter.Panel>
      </Splitter>
    </>
  )
}
