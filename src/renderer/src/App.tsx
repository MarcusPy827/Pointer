import { JSX, useState, useEffect, useCallback } from 'react'
import { ConfigProvider, theme } from 'antd'
import { WorkspaceContext } from './context/WorkspaceBridge'
import type { WorkspaceInfoQueryPayload } from '../../shared/BackendPromise'
import TitleBar from './components/TitleBar'
import ToolBar from './components/ToolBar'
import MyLibrary from './pages/MyLibrary'
import ErrNoWorkspaceOpened from './pages/ErrNoWorkspaceOpened'
import './assets/main.css'

export default function App(): JSX.Element {
  const darkModeQuery = window.matchMedia('(prefers-color-scheme: dark)')
  const workspaceStatePlaceholder: WorkspaceInfoQueryPayload = {
    query_state: false,
    err_msg: '⚙️ This is a placeholder and should be replaced after opening a workspace',
    err_code: -1,
    name: 'placeholder',
    owner_uid: '-1',
    owner_name: '%FRONTEND%',
    config_updated: 0,
    created_at: 0,
    version: 1,
    min_compatible_version: 1
  }

  const [darkMode, setDarkMode] = useState(false)
  const [isWorkspaceOpened, setIsWorkspaceOpened] = useState(false)
  const [workspacePath, setWorkspacePath] = useState('')
  const [workspaceState, setWorkspaceState] = useState(workspaceStatePlaceholder)

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
        <WorkspaceContext.Provider
          value={{
            isWorkspaceOpened,
            setIsWorkspaceOpened,
            workspacePath,
            setWorkspacePath,
            workspaceState,
            setWorkspaceState
          }}
        >
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
