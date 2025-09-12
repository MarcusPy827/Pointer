import { JSX, useState, useEffect, useCallback, useContext } from 'react'
import { ConfigProvider, theme } from 'antd'
import { WorkspaceContext } from './context/WorkspaceBridge'
import TitleBar from './components/TitleBar'
import ToolBar from './components/ToolBar'
import MyLibrary from './pages/MyLibrary'
import ErrNoWorkspaceOpened from './pages/ErrNoWorkspaceOpened'
import './assets/main.css'

export default function App(): JSX.Element {
  const [darkMode, setDarkMode] = useState(false)
  const [isWorkspaceOpened, setIsWorkspaceOpened] = useState(false)
  const darkModeQuery = window.matchMedia('(prefers-color-scheme: dark)')

  const onDarkModeChanged = useCallback((event: MediaQueryListEvent) => {
    setDarkMode(event.matches)
  }, [])

  useEffect(() => {
    darkModeQuery.addEventListener('change', onDarkModeChanged)
    return () => {
      darkModeQuery.removeEventListener('change', onDarkModeChanged)
    }
  }, [darkModeQuery, setDarkMode, onDarkModeChanged])

  useEffect(() => {
    setDarkMode(darkModeQuery.matches)
  }, [darkModeQuery.matches])

  return (
    <>
      <ConfigProvider
        theme={{ algorithm: darkMode ? theme.darkAlgorithm : theme.compactAlgorithm }}
      >
        <WorkspaceContext.Provider value={{ isWorkspaceOpened, setIsWorkspaceOpened }}>
          <TitleBar />
          <ToolBar />
          <div className="main-panel-container">
            <div className="side-panel">
              <div className="side-panel-content">[Work in progress...]</div>
            </div>

            <div className="content-panel">
              {isWorkspaceOpened ? <MyLibrary /> : <ErrNoWorkspaceOpened />}
            </div>
          </div>
        </WorkspaceContext.Provider>
      </ConfigProvider>
    </>
  )
}
