; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/slist.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.curl_slist = type { i8*, %struct.curl_slist* }

@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_cstrdup = external global i8* (i8*)*, align 8
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define %struct.curl_slist* @Curl_slist_append_nodup(%struct.curl_slist* %list, i8* %data) #0 !dbg !4 {
entry:
  %retval = alloca %struct.curl_slist*, align 8
  %list.addr = alloca %struct.curl_slist*, align 8
  %data.addr = alloca i8*, align 8
  %last = alloca %struct.curl_slist*, align 8
  %new_item = alloca %struct.curl_slist*, align 8
  store %struct.curl_slist* %list, %struct.curl_slist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %list.addr, metadata !30, metadata !31), !dbg !32
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !33, metadata !31), !dbg !34
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %last, metadata !35, metadata !31), !dbg !36
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %new_item, metadata !37, metadata !31), !dbg !38
  br label %do.body, !dbg !39

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !40

do.end:                                           ; preds = %do.body
  %0 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !43
  %call = call i8* %0(i64 16), !dbg !43
  %1 = bitcast i8* %call to %struct.curl_slist*, !dbg !43
  store %struct.curl_slist* %1, %struct.curl_slist** %new_item, align 8, !dbg !44
  %2 = load %struct.curl_slist*, %struct.curl_slist** %new_item, align 8, !dbg !45
  %tobool = icmp ne %struct.curl_slist* %2, null, !dbg !45
  br i1 %tobool, label %if.end, label %if.then, !dbg !47

if.then:                                          ; preds = %do.end
  store %struct.curl_slist* null, %struct.curl_slist** %retval, align 8, !dbg !48
  br label %return, !dbg !48

if.end:                                           ; preds = %do.end
  %3 = load %struct.curl_slist*, %struct.curl_slist** %new_item, align 8, !dbg !49
  %next = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %3, i32 0, i32 1, !dbg !50
  store %struct.curl_slist* null, %struct.curl_slist** %next, align 8, !dbg !51
  %4 = load i8*, i8** %data.addr, align 8, !dbg !52
  %5 = load %struct.curl_slist*, %struct.curl_slist** %new_item, align 8, !dbg !53
  %data1 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %5, i32 0, i32 0, !dbg !54
  store i8* %4, i8** %data1, align 8, !dbg !55
  %6 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !56
  %tobool2 = icmp ne %struct.curl_slist* %6, null, !dbg !56
  br i1 %tobool2, label %if.end4, label %if.then3, !dbg !58

if.then3:                                         ; preds = %if.end
  %7 = load %struct.curl_slist*, %struct.curl_slist** %new_item, align 8, !dbg !59
  store %struct.curl_slist* %7, %struct.curl_slist** %retval, align 8, !dbg !60
  br label %return, !dbg !60

if.end4:                                          ; preds = %if.end
  %8 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !61
  %call5 = call %struct.curl_slist* @slist_get_last(%struct.curl_slist* %8), !dbg !62
  store %struct.curl_slist* %call5, %struct.curl_slist** %last, align 8, !dbg !63
  %9 = load %struct.curl_slist*, %struct.curl_slist** %new_item, align 8, !dbg !64
  %10 = load %struct.curl_slist*, %struct.curl_slist** %last, align 8, !dbg !65
  %next6 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %10, i32 0, i32 1, !dbg !66
  store %struct.curl_slist* %9, %struct.curl_slist** %next6, align 8, !dbg !67
  %11 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !68
  store %struct.curl_slist* %11, %struct.curl_slist** %retval, align 8, !dbg !69
  br label %return, !dbg !69

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %12 = load %struct.curl_slist*, %struct.curl_slist** %retval, align 8, !dbg !70
  ret %struct.curl_slist* %12, !dbg !70
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal %struct.curl_slist* @slist_get_last(%struct.curl_slist* %list) #0 !dbg !26 {
entry:
  %retval = alloca %struct.curl_slist*, align 8
  %list.addr = alloca %struct.curl_slist*, align 8
  %item = alloca %struct.curl_slist*, align 8
  store %struct.curl_slist* %list, %struct.curl_slist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %list.addr, metadata !71, metadata !31), !dbg !72
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %item, metadata !73, metadata !31), !dbg !74
  %0 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !75
  %tobool = icmp ne %struct.curl_slist* %0, null, !dbg !75
  br i1 %tobool, label %if.end, label %if.then, !dbg !77

if.then:                                          ; preds = %entry
  store %struct.curl_slist* null, %struct.curl_slist** %retval, align 8, !dbg !78
  br label %return, !dbg !78

if.end:                                           ; preds = %entry
  %1 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !79
  store %struct.curl_slist* %1, %struct.curl_slist** %item, align 8, !dbg !80
  br label %while.cond, !dbg !81

while.cond:                                       ; preds = %while.body, %if.end
  %2 = load %struct.curl_slist*, %struct.curl_slist** %item, align 8, !dbg !82
  %next = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %2, i32 0, i32 1, !dbg !84
  %3 = load %struct.curl_slist*, %struct.curl_slist** %next, align 8, !dbg !84
  %tobool1 = icmp ne %struct.curl_slist* %3, null, !dbg !85
  br i1 %tobool1, label %while.body, label %while.end, !dbg !85

while.body:                                       ; preds = %while.cond
  %4 = load %struct.curl_slist*, %struct.curl_slist** %item, align 8, !dbg !86
  %next2 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %4, i32 0, i32 1, !dbg !88
  %5 = load %struct.curl_slist*, %struct.curl_slist** %next2, align 8, !dbg !88
  store %struct.curl_slist* %5, %struct.curl_slist** %item, align 8, !dbg !89
  br label %while.cond, !dbg !90

while.end:                                        ; preds = %while.cond
  %6 = load %struct.curl_slist*, %struct.curl_slist** %item, align 8, !dbg !92
  store %struct.curl_slist* %6, %struct.curl_slist** %retval, align 8, !dbg !93
  br label %return, !dbg !93

return:                                           ; preds = %while.end, %if.then
  %7 = load %struct.curl_slist*, %struct.curl_slist** %retval, align 8, !dbg !94
  ret %struct.curl_slist* %7, !dbg !94
}

; Function Attrs: nounwind uwtable
define %struct.curl_slist* @curl_slist_append(%struct.curl_slist* %list, i8* %data) #0 !dbg !15 {
entry:
  %retval = alloca %struct.curl_slist*, align 8
  %list.addr = alloca %struct.curl_slist*, align 8
  %data.addr = alloca i8*, align 8
  %dupdata = alloca i8*, align 8
  store %struct.curl_slist* %list, %struct.curl_slist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %list.addr, metadata !95, metadata !31), !dbg !96
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !97, metadata !31), !dbg !98
  call void @llvm.dbg.declare(metadata i8** %dupdata, metadata !99, metadata !31), !dbg !100
  %0 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !101
  %1 = load i8*, i8** %data.addr, align 8, !dbg !101
  %call = call i8* %0(i8* %1), !dbg !101
  store i8* %call, i8** %dupdata, align 8, !dbg !100
  %2 = load i8*, i8** %dupdata, align 8, !dbg !102
  %tobool = icmp ne i8* %2, null, !dbg !102
  br i1 %tobool, label %if.end, label %if.then, !dbg !104

if.then:                                          ; preds = %entry
  store %struct.curl_slist* null, %struct.curl_slist** %retval, align 8, !dbg !105
  br label %return, !dbg !105

if.end:                                           ; preds = %entry
  %3 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !106
  %4 = load i8*, i8** %dupdata, align 8, !dbg !107
  %call1 = call %struct.curl_slist* @Curl_slist_append_nodup(%struct.curl_slist* %3, i8* %4), !dbg !108
  store %struct.curl_slist* %call1, %struct.curl_slist** %list.addr, align 8, !dbg !109
  %5 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !110
  %tobool2 = icmp ne %struct.curl_slist* %5, null, !dbg !110
  br i1 %tobool2, label %if.end4, label %if.then3, !dbg !112

if.then3:                                         ; preds = %if.end
  %6 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !113
  %7 = load i8*, i8** %dupdata, align 8, !dbg !113
  call void %6(i8* %7), !dbg !113
  br label %if.end4, !dbg !113

if.end4:                                          ; preds = %if.then3, %if.end
  %8 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !114
  store %struct.curl_slist* %8, %struct.curl_slist** %retval, align 8, !dbg !115
  br label %return, !dbg !115

return:                                           ; preds = %if.end4, %if.then
  %9 = load %struct.curl_slist*, %struct.curl_slist** %retval, align 8, !dbg !116
  ret %struct.curl_slist* %9, !dbg !116
}

; Function Attrs: nounwind uwtable
define %struct.curl_slist* @Curl_slist_duplicate(%struct.curl_slist* %inlist) #0 !dbg !20 {
entry:
  %retval = alloca %struct.curl_slist*, align 8
  %inlist.addr = alloca %struct.curl_slist*, align 8
  %outlist = alloca %struct.curl_slist*, align 8
  %tmp = alloca %struct.curl_slist*, align 8
  store %struct.curl_slist* %inlist, %struct.curl_slist** %inlist.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %inlist.addr, metadata !117, metadata !31), !dbg !118
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %outlist, metadata !119, metadata !31), !dbg !120
  store %struct.curl_slist* null, %struct.curl_slist** %outlist, align 8, !dbg !120
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %tmp, metadata !121, metadata !31), !dbg !122
  br label %while.cond, !dbg !123

while.cond:                                       ; preds = %if.end, %entry
  %0 = load %struct.curl_slist*, %struct.curl_slist** %inlist.addr, align 8, !dbg !124
  %tobool = icmp ne %struct.curl_slist* %0, null, !dbg !126
  br i1 %tobool, label %while.body, label %while.end, !dbg !126

while.body:                                       ; preds = %while.cond
  %1 = load %struct.curl_slist*, %struct.curl_slist** %outlist, align 8, !dbg !127
  %2 = load %struct.curl_slist*, %struct.curl_slist** %inlist.addr, align 8, !dbg !129
  %data = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %2, i32 0, i32 0, !dbg !130
  %3 = load i8*, i8** %data, align 8, !dbg !130
  %call = call %struct.curl_slist* @curl_slist_append(%struct.curl_slist* %1, i8* %3), !dbg !131
  store %struct.curl_slist* %call, %struct.curl_slist** %tmp, align 8, !dbg !132
  %4 = load %struct.curl_slist*, %struct.curl_slist** %tmp, align 8, !dbg !133
  %tobool1 = icmp ne %struct.curl_slist* %4, null, !dbg !133
  br i1 %tobool1, label %if.end, label %if.then, !dbg !135

if.then:                                          ; preds = %while.body
  %5 = load %struct.curl_slist*, %struct.curl_slist** %outlist, align 8, !dbg !136
  call void @curl_slist_free_all(%struct.curl_slist* %5), !dbg !138
  store %struct.curl_slist* null, %struct.curl_slist** %retval, align 8, !dbg !139
  br label %return, !dbg !139

if.end:                                           ; preds = %while.body
  %6 = load %struct.curl_slist*, %struct.curl_slist** %tmp, align 8, !dbg !140
  store %struct.curl_slist* %6, %struct.curl_slist** %outlist, align 8, !dbg !141
  %7 = load %struct.curl_slist*, %struct.curl_slist** %inlist.addr, align 8, !dbg !142
  %next = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %7, i32 0, i32 1, !dbg !143
  %8 = load %struct.curl_slist*, %struct.curl_slist** %next, align 8, !dbg !143
  store %struct.curl_slist* %8, %struct.curl_slist** %inlist.addr, align 8, !dbg !144
  br label %while.cond, !dbg !145

while.end:                                        ; preds = %while.cond
  %9 = load %struct.curl_slist*, %struct.curl_slist** %outlist, align 8, !dbg !147
  store %struct.curl_slist* %9, %struct.curl_slist** %retval, align 8, !dbg !148
  br label %return, !dbg !148

return:                                           ; preds = %while.end, %if.then
  %10 = load %struct.curl_slist*, %struct.curl_slist** %retval, align 8, !dbg !149
  ret %struct.curl_slist* %10, !dbg !149
}

; Function Attrs: nounwind uwtable
define void @curl_slist_free_all(%struct.curl_slist* %list) #0 !dbg !23 {
entry:
  %list.addr = alloca %struct.curl_slist*, align 8
  %next = alloca %struct.curl_slist*, align 8
  %item = alloca %struct.curl_slist*, align 8
  store %struct.curl_slist* %list, %struct.curl_slist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %list.addr, metadata !150, metadata !31), !dbg !151
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %next, metadata !152, metadata !31), !dbg !153
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %item, metadata !154, metadata !31), !dbg !155
  %0 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !156
  %tobool = icmp ne %struct.curl_slist* %0, null, !dbg !156
  br i1 %tobool, label %if.end, label %if.then, !dbg !158

if.then:                                          ; preds = %entry
  br label %do.end5, !dbg !159

if.end:                                           ; preds = %entry
  %1 = load %struct.curl_slist*, %struct.curl_slist** %list.addr, align 8, !dbg !160
  store %struct.curl_slist* %1, %struct.curl_slist** %item, align 8, !dbg !161
  br label %do.body, !dbg !162

do.body:                                          ; preds = %do.cond, %if.end
  %2 = load %struct.curl_slist*, %struct.curl_slist** %item, align 8, !dbg !163
  %next1 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %2, i32 0, i32 1, !dbg !165
  %3 = load %struct.curl_slist*, %struct.curl_slist** %next1, align 8, !dbg !165
  store %struct.curl_slist* %3, %struct.curl_slist** %next, align 8, !dbg !166
  br label %do.body2, !dbg !167

do.body2:                                         ; preds = %do.body
  %4 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !168
  %5 = load %struct.curl_slist*, %struct.curl_slist** %item, align 8, !dbg !168
  %data = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %5, i32 0, i32 0, !dbg !168
  %6 = load i8*, i8** %data, align 8, !dbg !168
  call void %4(i8* %6), !dbg !168
  %7 = load %struct.curl_slist*, %struct.curl_slist** %item, align 8, !dbg !168
  %data3 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %7, i32 0, i32 0, !dbg !168
  store i8* null, i8** %data3, align 8, !dbg !168
  br label %do.end, !dbg !168

do.end:                                           ; preds = %do.body2
  %8 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !171
  %9 = load %struct.curl_slist*, %struct.curl_slist** %item, align 8, !dbg !171
  %10 = bitcast %struct.curl_slist* %9 to i8*, !dbg !171
  call void %8(i8* %10), !dbg !171
  %11 = load %struct.curl_slist*, %struct.curl_slist** %next, align 8, !dbg !172
  store %struct.curl_slist* %11, %struct.curl_slist** %item, align 8, !dbg !173
  br label %do.cond, !dbg !174

do.cond:                                          ; preds = %do.end
  %12 = load %struct.curl_slist*, %struct.curl_slist** %next, align 8, !dbg !175
  %tobool4 = icmp ne %struct.curl_slist* %12, null, !dbg !177
  br i1 %tobool4, label %do.body, label %do.end5, !dbg !177

do.end5:                                          ; preds = %if.then, %do.cond
  ret void, !dbg !178
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!27, !28}
!llvm.ident = !{!29}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/slist.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !15, !20, !23, !26}
!4 = distinct !DISubprogram(name: "Curl_slist_append_nodup", scope: !1, file: !1, line: 59, type: !5, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !12}
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !9, line: 2176, size: 128, align: 64, elements: !10)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!10 = !{!11, !14}
!11 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !8, file: !9, line: 2177, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !8, file: !9, line: 2178, baseType: !7, size: 64, align: 64, offset: 64)
!15 = distinct !DISubprogram(name: "curl_slist_append", scope: !1, file: !1, line: 89, type: !16, isLocal: false, isDefinition: true, scopeLine: 91, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!16 = !DISubroutineType(types: !17)
!17 = !{!7, !7, !18}
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!20 = distinct !DISubprogram(name: "Curl_slist_duplicate", scope: !1, file: !1, line: 109, type: !21, isLocal: false, isDefinition: true, scopeLine: 110, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!21 = !DISubroutineType(types: !22)
!22 = !{!7, !7}
!23 = distinct !DISubprogram(name: "curl_slist_free_all", scope: !1, file: !1, line: 129, type: !24, isLocal: false, isDefinition: true, scopeLine: 130, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!24 = !DISubroutineType(types: !25)
!25 = !{null, !7}
!26 = distinct !DISubprogram(name: "slist_get_last", scope: !1, file: !1, line: 34, type: !21, isLocal: true, isDefinition: true, scopeLine: 35, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!27 = !{i32 2, !"Dwarf Version", i32 4}
!28 = !{i32 2, !"Debug Info Version", i32 3}
!29 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!30 = !DILocalVariable(name: "list", arg: 1, scope: !4, file: !1, line: 59, type: !7)
!31 = !DIExpression()
!32 = !DILocation(line: 59, column: 63, scope: !4)
!33 = !DILocalVariable(name: "data", arg: 2, scope: !4, file: !1, line: 59, type: !12)
!34 = !DILocation(line: 59, column: 75, scope: !4)
!35 = !DILocalVariable(name: "last", scope: !4, file: !1, line: 61, type: !7)
!36 = !DILocation(line: 61, column: 26, scope: !4)
!37 = !DILocalVariable(name: "new_item", scope: !4, file: !1, line: 62, type: !7)
!38 = !DILocation(line: 62, column: 26, scope: !4)
!39 = !DILocation(line: 64, column: 3, scope: !4)
!40 = !DILocation(line: 64, column: 3, scope: !41)
!41 = !DILexicalBlockFile(scope: !42, file: !1, discriminator: 1)
!42 = distinct !DILexicalBlock(scope: !4, file: !1, line: 64, column: 3)
!43 = !DILocation(line: 66, column: 14, scope: !4)
!44 = !DILocation(line: 66, column: 12, scope: !4)
!45 = !DILocation(line: 67, column: 7, scope: !46)
!46 = distinct !DILexicalBlock(scope: !4, file: !1, line: 67, column: 6)
!47 = !DILocation(line: 67, column: 6, scope: !4)
!48 = !DILocation(line: 68, column: 5, scope: !46)
!49 = !DILocation(line: 70, column: 3, scope: !4)
!50 = !DILocation(line: 70, column: 13, scope: !4)
!51 = !DILocation(line: 70, column: 18, scope: !4)
!52 = !DILocation(line: 71, column: 20, scope: !4)
!53 = !DILocation(line: 71, column: 3, scope: !4)
!54 = !DILocation(line: 71, column: 13, scope: !4)
!55 = !DILocation(line: 71, column: 18, scope: !4)
!56 = !DILocation(line: 74, column: 7, scope: !57)
!57 = distinct !DILexicalBlock(scope: !4, file: !1, line: 74, column: 6)
!58 = !DILocation(line: 74, column: 6, scope: !4)
!59 = !DILocation(line: 75, column: 12, scope: !57)
!60 = !DILocation(line: 75, column: 5, scope: !57)
!61 = !DILocation(line: 77, column: 25, scope: !4)
!62 = !DILocation(line: 77, column: 10, scope: !4)
!63 = !DILocation(line: 77, column: 8, scope: !4)
!64 = !DILocation(line: 78, column: 16, scope: !4)
!65 = !DILocation(line: 78, column: 3, scope: !4)
!66 = !DILocation(line: 78, column: 9, scope: !4)
!67 = !DILocation(line: 78, column: 14, scope: !4)
!68 = !DILocation(line: 79, column: 10, scope: !4)
!69 = !DILocation(line: 79, column: 3, scope: !4)
!70 = !DILocation(line: 80, column: 1, scope: !4)
!71 = !DILocalVariable(name: "list", arg: 1, scope: !26, file: !1, line: 34, type: !7)
!72 = !DILocation(line: 34, column: 61, scope: !26)
!73 = !DILocalVariable(name: "item", scope: !26, file: !1, line: 36, type: !7)
!74 = !DILocation(line: 36, column: 26, scope: !26)
!75 = !DILocation(line: 39, column: 7, scope: !76)
!76 = distinct !DILexicalBlock(scope: !26, file: !1, line: 39, column: 6)
!77 = !DILocation(line: 39, column: 6, scope: !26)
!78 = !DILocation(line: 40, column: 5, scope: !76)
!79 = !DILocation(line: 43, column: 10, scope: !26)
!80 = !DILocation(line: 43, column: 8, scope: !26)
!81 = !DILocation(line: 44, column: 3, scope: !26)
!82 = !DILocation(line: 44, column: 9, scope: !83)
!83 = !DILexicalBlockFile(scope: !26, file: !1, discriminator: 1)
!84 = !DILocation(line: 44, column: 15, scope: !83)
!85 = !DILocation(line: 44, column: 3, scope: !83)
!86 = !DILocation(line: 45, column: 12, scope: !87)
!87 = distinct !DILexicalBlock(scope: !26, file: !1, line: 44, column: 21)
!88 = !DILocation(line: 45, column: 18, scope: !87)
!89 = !DILocation(line: 45, column: 10, scope: !87)
!90 = !DILocation(line: 44, column: 3, scope: !91)
!91 = !DILexicalBlockFile(scope: !26, file: !1, discriminator: 2)
!92 = !DILocation(line: 47, column: 10, scope: !26)
!93 = !DILocation(line: 47, column: 3, scope: !26)
!94 = !DILocation(line: 48, column: 1, scope: !26)
!95 = !DILocalVariable(name: "list", arg: 1, scope: !15, file: !1, line: 89, type: !7)
!96 = !DILocation(line: 89, column: 57, scope: !15)
!97 = !DILocalVariable(name: "data", arg: 2, scope: !15, file: !1, line: 90, type: !18)
!98 = !DILocation(line: 90, column: 50, scope: !15)
!99 = !DILocalVariable(name: "dupdata", scope: !15, file: !1, line: 92, type: !12)
!100 = !DILocation(line: 92, column: 9, scope: !15)
!101 = !DILocation(line: 92, column: 19, scope: !15)
!102 = !DILocation(line: 94, column: 7, scope: !103)
!103 = distinct !DILexicalBlock(scope: !15, file: !1, line: 94, column: 6)
!104 = !DILocation(line: 94, column: 6, scope: !15)
!105 = !DILocation(line: 95, column: 5, scope: !103)
!106 = !DILocation(line: 97, column: 34, scope: !15)
!107 = !DILocation(line: 97, column: 40, scope: !15)
!108 = !DILocation(line: 97, column: 10, scope: !15)
!109 = !DILocation(line: 97, column: 8, scope: !15)
!110 = !DILocation(line: 98, column: 7, scope: !111)
!111 = distinct !DILexicalBlock(scope: !15, file: !1, line: 98, column: 6)
!112 = !DILocation(line: 98, column: 6, scope: !15)
!113 = !DILocation(line: 99, column: 5, scope: !111)
!114 = !DILocation(line: 101, column: 10, scope: !15)
!115 = !DILocation(line: 101, column: 3, scope: !15)
!116 = !DILocation(line: 102, column: 1, scope: !15)
!117 = !DILocalVariable(name: "inlist", arg: 1, scope: !20, file: !1, line: 109, type: !7)
!118 = !DILocation(line: 109, column: 60, scope: !20)
!119 = !DILocalVariable(name: "outlist", scope: !20, file: !1, line: 111, type: !7)
!120 = !DILocation(line: 111, column: 22, scope: !20)
!121 = !DILocalVariable(name: "tmp", scope: !20, file: !1, line: 112, type: !7)
!122 = !DILocation(line: 112, column: 22, scope: !20)
!123 = !DILocation(line: 114, column: 3, scope: !20)
!124 = !DILocation(line: 114, column: 9, scope: !125)
!125 = !DILexicalBlockFile(scope: !20, file: !1, discriminator: 1)
!126 = !DILocation(line: 114, column: 3, scope: !125)
!127 = !DILocation(line: 115, column: 29, scope: !128)
!128 = distinct !DILexicalBlock(scope: !20, file: !1, line: 114, column: 17)
!129 = !DILocation(line: 115, column: 38, scope: !128)
!130 = !DILocation(line: 115, column: 46, scope: !128)
!131 = !DILocation(line: 115, column: 11, scope: !128)
!132 = !DILocation(line: 115, column: 9, scope: !128)
!133 = !DILocation(line: 117, column: 9, scope: !134)
!134 = distinct !DILexicalBlock(scope: !128, file: !1, line: 117, column: 8)
!135 = !DILocation(line: 117, column: 8, scope: !128)
!136 = !DILocation(line: 118, column: 27, scope: !137)
!137 = distinct !DILexicalBlock(scope: !134, file: !1, line: 117, column: 14)
!138 = !DILocation(line: 118, column: 7, scope: !137)
!139 = !DILocation(line: 119, column: 7, scope: !137)
!140 = !DILocation(line: 122, column: 15, scope: !128)
!141 = !DILocation(line: 122, column: 13, scope: !128)
!142 = !DILocation(line: 123, column: 14, scope: !128)
!143 = !DILocation(line: 123, column: 22, scope: !128)
!144 = !DILocation(line: 123, column: 12, scope: !128)
!145 = !DILocation(line: 114, column: 3, scope: !146)
!146 = !DILexicalBlockFile(scope: !20, file: !1, discriminator: 2)
!147 = !DILocation(line: 125, column: 10, scope: !20)
!148 = !DILocation(line: 125, column: 3, scope: !20)
!149 = !DILocation(line: 126, column: 1, scope: !20)
!150 = !DILocalVariable(name: "list", arg: 1, scope: !23, file: !1, line: 129, type: !7)
!151 = !DILocation(line: 129, column: 45, scope: !23)
!152 = !DILocalVariable(name: "next", scope: !23, file: !1, line: 131, type: !7)
!153 = !DILocation(line: 131, column: 26, scope: !23)
!154 = !DILocalVariable(name: "item", scope: !23, file: !1, line: 132, type: !7)
!155 = !DILocation(line: 132, column: 26, scope: !23)
!156 = !DILocation(line: 134, column: 7, scope: !157)
!157 = distinct !DILexicalBlock(scope: !23, file: !1, line: 134, column: 6)
!158 = !DILocation(line: 134, column: 6, scope: !23)
!159 = !DILocation(line: 135, column: 5, scope: !157)
!160 = !DILocation(line: 137, column: 10, scope: !23)
!161 = !DILocation(line: 137, column: 8, scope: !23)
!162 = !DILocation(line: 138, column: 3, scope: !23)
!163 = !DILocation(line: 139, column: 12, scope: !164)
!164 = distinct !DILexicalBlock(scope: !23, file: !1, line: 138, column: 6)
!165 = !DILocation(line: 139, column: 18, scope: !164)
!166 = !DILocation(line: 139, column: 10, scope: !164)
!167 = !DILocation(line: 140, column: 5, scope: !164)
!168 = !DILocation(line: 140, column: 5, scope: !169)
!169 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 1)
!170 = distinct !DILexicalBlock(scope: !164, file: !1, line: 140, column: 5)
!171 = !DILocation(line: 141, column: 5, scope: !164)
!172 = !DILocation(line: 142, column: 12, scope: !164)
!173 = !DILocation(line: 142, column: 10, scope: !164)
!174 = !DILocation(line: 143, column: 3, scope: !164)
!175 = !DILocation(line: 143, column: 11, scope: !176)
!176 = !DILexicalBlockFile(scope: !23, file: !1, discriminator: 1)
!177 = !DILocation(line: 143, column: 3, scope: !176)
!178 = !DILocation(line: 144, column: 1, scope: !23)
