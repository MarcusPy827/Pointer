import { ElectronAPI } from '@electron-toolkit/preload'
import { WindowCommandType } from '../shared/WindowCommandType'
import { FolderPath } from "../shared/FolderPath"

interface RenderAPI {
  resizeWindowFunc: (type: WindowCommandType) => Promise<void>,
  openFolderFunc: () => Promise<FolderPath>
}

declare global {
  interface Window {
    electron: ElectronAPI
    api: unknown
  }
}
