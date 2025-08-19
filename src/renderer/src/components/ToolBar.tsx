import { JSX } from "react"

export default function ToolBar(): JSX.Element {
  return (
    <>
      <div className="tool-bar">
        <span className="tool-bar-title no-select" draggable={false}>My Library</span>
        <span className="tool-bar-subtitle no-select" draggable={false}>My Library</span>
      </div>
    </>
  )
}
