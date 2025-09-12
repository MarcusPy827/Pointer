import {
  JSX,
  Context,
  useState,
  useEffect,
  useCallback,
  createContext,
  useMemo,
  useContext
} from 'react'
import { ConfigProvider, theme } from 'antd'
import TitleBar from './components/TitleBar'
import ToolBar from './components/ToolBar'
import MyLibrary from './pages/MyLibrary'
import ErrNoWorkspaceOpened from './pages/ErrNoWorkspaceOpened'
import './assets/main.css'

const WorkspaceStateContext: Context<{}> = createContext({})
const workspacePathContext: Context<{}> = createContext({})

function WorkspaceConfigProvider({ children }) {
  const [isWorkspaceOpened, setIsWorkspaceOpened] = useState(false)
  const [workspacePath, setWorkspacePath] = useState('')

  const isWsOpen = useMemo(() => ({ isWorkspaceOpened, setIsWorkspaceOpened }), [isWorkspaceOpened])

  const wsPath = useMemo(() => ({ workspacePath, setWorkspacePath }), [workspacePath])

  return (
    <>
      <WorkspaceStateContext.Provider value={isWsOpen}>
        <workspacePathContext.Provider value={wsPath}>{children}</workspacePathContext.Provider>
      </WorkspaceStateContext.Provider>
    </>
  )
}

function useWorkspaceOpened() {
  return useContext(WorkspaceStateContext)
}

function useWorkspacePath() {
  return useContext(workspacePathContext)
}

export default function App(): JSX.Element {
  const [darkMode, setDarkMode] = useState(false)
  const darkModeQuery = window.matchMedia('(prefers-color-scheme: dark)')

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
  }, [])

  const { isWorkspaceOpened, setIsWorkspaceOpened } = useWorkspaceOpened()

  return (
    <>
      <ConfigProvider
        theme={{ algorithm: darkMode ? theme.darkAlgorithm : theme.compactAlgorithm }}
      >
        <WorkspaceConfigProvider>
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
        </WorkspaceConfigProvider>
      </ConfigProvider>
    </>
  )
}
