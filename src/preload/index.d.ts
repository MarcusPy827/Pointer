import { ElectronAPI } from '@electron-toolkit/preload'
import { WindowCommandType } from '../shared/WindowCommandType'

interface RenderAPI {
  resizeWindowFunc: (type: WindowCommandType) => Promise<void>
}

declare global {
  interface Window {
    electron: ElectronAPI
    api: unknown
  }
}
