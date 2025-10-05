import { JSX, useState } from 'react'
import { message } from 'antd'
import { useTranslation } from 'react-i18next'
import { FileUnknownOutlined, FileOutlined, FolderOutlined } from '@ant-design/icons'
import {
  DirectoryQueryResult,
  DirectoryQuery
} from '../../../shared/proto_gen/src/proto/file_handler'
import type { TreeDataNode } from 'antd'

export function GetDirectoryNodeIcon({
  isFile,
  isUnknown
}: {
  isFile: boolean
  isUnknown: boolean
}): JSX.Element {
  let result: JSX.Element
  if (isUnknown) {
    result = <FileUnknownOutlined />
  } else if (isFile) {
    result = <FileOutlined />
  } else {
    result = <FolderOutlined />
  }
  return result
}

export function GenFileTree({ workspacePath, onFileSelect }): JSX.Element {
  const [treeData, setTreeData] = useState<TreeDataNode[]>([])
  const [loading, setLoading] = useState(false)
  const [messageApi, contextHolder] = message.useMessage()
  const { t } = useTranslation()

  const fetchDirectory = async (path: string): Promise<TreeDataNode[]> => {
    try {
      //@ts-ignore: Alreade defined in preload
      const result: DirectoryQueryResult = await window.api.listDirectoryFunc(path)
      if (!result.queryState?.result) {
        messageApi.open({
          type: 'error',
          content: t('err_cannot_read_workspace')
        })
        console.error(
          `Cannot read directory from the folder. The backend returned: ${result.queryState?.errMsg}`
        )
        return []
      }
      return result.payload.map((entry: DirectoryQuery) => ({
        title: entry.name,
        key: entry.path,
        isLeaf: entry.isFile || entry.isTypeUnknown,
        icon: GetDirectoryNodeIcon({ isFile: entry.isFile, isUnknown: entry.isTypeUnknown })
      }))
    } catch (err) {
      messageApi.open({
        type: 'error',
        content: t('err_cannot_read_workspace')
      })
      console.error(`Cannot read directory from the folder. The frontend returned: ${String(err)}`)
      return []
    }
  }

  return (
    <>
      {contextHolder}
      <p>Work in progress...</p>
    </>
  )
}

export default function SidePane({ workspacePath, onFileSelect }): JSX.Element {
  return (
    <>
      <GenFileTree workspacePath={workspacePath} onFileSelect={onFileSelect} />
    </>
  )
}
