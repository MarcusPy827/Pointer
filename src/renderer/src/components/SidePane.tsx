import { JSX, useState, useCallback, useEffect } from 'react'
import { message, Tree, Spin, Empty } from 'antd'
import { useTranslation } from 'react-i18next'
import { FileUnknownOutlined, FileOutlined, FolderOutlined } from '@ant-design/icons'
import {
  DirectoryQueryResult,
  DirectoryQuery
} from '../../../shared/proto_gen/src/proto/file_handler'
import type { TreeDataNode } from 'antd'
import type { EventDataNode } from 'antd/es/tree'

interface SidePaneProps {
  workspacePath: string
  onFileSelect: (filePath: string) => void
}

interface GenFileTreeProps {
  workspacePath: string
  onFileSelect: (filePath: string) => void
}

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

export function GenFileTree({ workspacePath, onFileSelect }: GenFileTreeProps): JSX.Element {
  const [treeData, setTreeData] = useState<TreeDataNode[]>([])
  const [loading, setLoading] = useState(false)
  const [messageApi, contextHolder] = message.useMessage()
  const { t } = useTranslation()

  const fetchDirectory = useCallback(
    async (path: string): Promise<TreeDataNode[]> => {
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
        console.error(
          `Cannot read directory from the folder. The frontend returned: ${String(err)}`
        )
        return []
      }
    },
    [messageApi, t]
  )

  useEffect(() => {
    if (!workspacePath) {
      setTreeData([])
      return
    }

    setLoading(true)
    fetchDirectory(workspacePath)
      .then((data) => setTreeData(data))
      .finally(() => setLoading(false))
  }, [workspacePath, fetchDirectory])

  const onLoadData = async (treeNode: EventDataNode<TreeDataNode>): Promise<void> => {
    if (treeNode.children) return
    const children = await fetchDirectory(String(treeNode.key))
    setTreeData((origin) =>
      origin.map((node) => (node.key === treeNode.key ? { ...node, children } : node))
    )
  }

  if (!workspacePath) {
    return (
      <>
        {contextHolder}
        <div style={{ textAlign: 'center', paddingTop: 60 }}>
          <Empty description="No workspace selected" />
        </div>
      </>
    )
  }

  return (
    <>
      {contextHolder}
      <Spin spinning={loading}>
        <Tree
          showIcon
          loadData={onLoadData}
          treeData={treeData}
          onSelect={(selectedKeys) => {
            if (selectedKeys.length > 0) {
              onFileSelect(String(selectedKeys[0]))
            }
          }}
          defaultExpandAll={false}
          style={{ userSelect: 'none', fontSize: 16, lineHeight: 22, background: 'transparent !important' }}
          showLine={true}
        />
      </Spin>
    </>
  )
}

export default function SidePane({ workspacePath, onFileSelect }: SidePaneProps): JSX.Element {
  return (
    <>
      <GenFileTree workspacePath={workspacePath} onFileSelect={onFileSelect} />
    </>
  )
}
