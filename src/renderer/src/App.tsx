import { JSX, useState, useEffect, useCallback } from "react"
import {ConfigProvider, Splitter, theme} from "antd"
import TitleBar from "./components/TitleBar"
import ToolBar from "./components/ToolBar"
import MyLibrary from "./pages/MyLibrary"
import "./assets/main.css"

export default function App(): JSX.Element {
  const [darkMode, setDarkMode] = useState(false)
  const darkModeQuery = window.matchMedia("(prefers-color-scheme: dark)")

  const onDarkModeChanged = useCallback((event: MediaQueryListEvent) => {
    setDarkMode(event.matches)
  }, [])

  useEffect(() => {
    darkModeQuery.addEventListener('change', onDarkModeChanged)
    return () => {
      darkModeQuery.removeEventListener('change', onDarkModeChanged)
    }
  }, [darkModeQuery, darkModeQuery])

  useEffect(() => {
    setDarkMode(darkModeQuery.matches)
  }, []);

  return (
    <>
      <ConfigProvider theme={{ algorithm: darkMode ? theme.darkAlgorithm : theme.compactAlgorithm }}>
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
      </ConfigProvider>
    </>
  )
}
