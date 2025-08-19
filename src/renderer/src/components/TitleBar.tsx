import { JSX } from "react"
import { getAppVersionString } from "./Versions"
import { WindowCommandType } from "../../../shared/WindowCommandType"
import "mdui/dist/css/mdui.min.css"
import "mdui/dist/js/mdui.min.js"

export default function TitleBar(): JSX.Element {
  const onWindowResize = async (type: WindowCommandType): Promise<void> => {
    // @ts-ignore API field already defined in preload
    await window.api.resizeWindowFunc(type)
  }
  return (
    <>
      <div className="title-bar no-select">
        <div className="title-bar-section no-select">
          <span className="app-title no-select" draggable={false}>Pointer</span>
          <span className="app-version no-select" draggable={false}>REL {getAppVersionString()}</span>
        </div>

        <div className="title-bar-btn-section no-select">
          <button
            className="mdui-btn mdui-btn-icon mdui-ripple mdui-ripple-light-blue no-select"
            draggable={false}
            onClick={() => onWindowResize(WindowCommandType.kMinimize)}>
            <i className="mdui-icon material-icons">&#xe15b;</i>
          </button>
          <button
            className="mdui-btn mdui-btn-icon mdui-ripple mdui-ripple-light-blue no-select"
            draggable={false}
            onClick={() => onWindowResize(WindowCommandType.kMaximize)}>
            <i className="mdui-icon material-icons">&#xe3c6;</i>
          </button>
          <button
            className="mdui-btn mdui-btn-icon mdui-ripple mdui-ripple-red no-select"
            draggable={false}
            onClick={() => onWindowResize(WindowCommandType.kClose)}>
            <i className="mdui-icon material-icons no-select" draggable={false}>&#xe5cd;</i>
          </button>
        </div>
      </div>
    </>
  )
}
