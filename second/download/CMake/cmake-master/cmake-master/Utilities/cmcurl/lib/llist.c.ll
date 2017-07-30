; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }

@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define void @Curl_llist_init(%struct.curl_llist* %l, void (i8*, i8*)* %dtor) #0 !dbg !6 {
entry:
  %l.addr = alloca %struct.curl_llist*, align 8
  %dtor.addr = alloca void (i8*, i8*)*, align 8
  store %struct.curl_llist* %l, %struct.curl_llist** %l.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %l.addr, metadata !51, metadata !52), !dbg !53
  store void (i8*, i8*)* %dtor, void (i8*, i8*)** %dtor.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*, i8*)** %dtor.addr, metadata !54, metadata !52), !dbg !55
  %0 = load %struct.curl_llist*, %struct.curl_llist** %l.addr, align 8, !dbg !56
  %size = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %0, i32 0, i32 3, !dbg !57
  store i64 0, i64* %size, align 8, !dbg !58
  %1 = load void (i8*, i8*)*, void (i8*, i8*)** %dtor.addr, align 8, !dbg !59
  %2 = load %struct.curl_llist*, %struct.curl_llist** %l.addr, align 8, !dbg !60
  %dtor1 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %2, i32 0, i32 2, !dbg !61
  store void (i8*, i8*)* %1, void (i8*, i8*)** %dtor1, align 8, !dbg !62
  %3 = load %struct.curl_llist*, %struct.curl_llist** %l.addr, align 8, !dbg !63
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %3, i32 0, i32 0, !dbg !64
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %head, align 8, !dbg !65
  %4 = load %struct.curl_llist*, %struct.curl_llist** %l.addr, align 8, !dbg !66
  %tail = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %4, i32 0, i32 1, !dbg !67
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %tail, align 8, !dbg !68
  ret void, !dbg !69
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @Curl_llist_insert_next(%struct.curl_llist* %list, %struct.curl_llist_element* %e, i8* %p) #0 !dbg !30 {
entry:
  %retval = alloca i32, align 4
  %list.addr = alloca %struct.curl_llist*, align 8
  %e.addr = alloca %struct.curl_llist_element*, align 8
  %p.addr = alloca i8*, align 8
  %ne = alloca %struct.curl_llist_element*, align 8
  store %struct.curl_llist* %list, %struct.curl_llist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %list.addr, metadata !70, metadata !52), !dbg !71
  store %struct.curl_llist_element* %e, %struct.curl_llist_element** %e.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %e.addr, metadata !72, metadata !52), !dbg !73
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !74, metadata !52), !dbg !75
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %ne, metadata !76, metadata !52), !dbg !77
  %0 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !78
  %call = call i8* %0(i64 24), !dbg !78
  %1 = bitcast i8* %call to %struct.curl_llist_element*, !dbg !78
  store %struct.curl_llist_element* %1, %struct.curl_llist_element** %ne, align 8, !dbg !77
  %2 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !79
  %tobool = icmp ne %struct.curl_llist_element* %2, null, !dbg !79
  br i1 %tobool, label %if.end, label %if.then, !dbg !81

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !82
  br label %return, !dbg !82

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %p.addr, align 8, !dbg !83
  %4 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !84
  %ptr = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %4, i32 0, i32 0, !dbg !85
  store i8* %3, i8** %ptr, align 8, !dbg !86
  %5 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !87
  %size = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %5, i32 0, i32 3, !dbg !89
  %6 = load i64, i64* %size, align 8, !dbg !89
  %cmp = icmp eq i64 %6, 0, !dbg !90
  br i1 %cmp, label %if.then1, label %if.else, !dbg !91

if.then1:                                         ; preds = %if.end
  %7 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !92
  %8 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !94
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %8, i32 0, i32 0, !dbg !95
  store %struct.curl_llist_element* %7, %struct.curl_llist_element** %head, align 8, !dbg !96
  %9 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !97
  %head2 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %9, i32 0, i32 0, !dbg !98
  %10 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head2, align 8, !dbg !98
  %prev = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %10, i32 0, i32 1, !dbg !99
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %prev, align 8, !dbg !100
  %11 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !101
  %head3 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %11, i32 0, i32 0, !dbg !102
  %12 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head3, align 8, !dbg !102
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %12, i32 0, i32 2, !dbg !103
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %next, align 8, !dbg !104
  %13 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !105
  %14 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !106
  %tail = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %14, i32 0, i32 1, !dbg !107
  store %struct.curl_llist_element* %13, %struct.curl_llist_element** %tail, align 8, !dbg !108
  br label %if.end28, !dbg !109

if.else:                                          ; preds = %if.end
  %15 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !110
  %tobool4 = icmp ne %struct.curl_llist_element* %15, null, !dbg !110
  br i1 %tobool4, label %cond.true, label %cond.false, !dbg !110

cond.true:                                        ; preds = %if.else
  %16 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !112
  %next5 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %16, i32 0, i32 2, !dbg !114
  %17 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next5, align 8, !dbg !114
  br label %cond.end, !dbg !115

cond.false:                                       ; preds = %if.else
  %18 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !116
  %head6 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %18, i32 0, i32 0, !dbg !118
  %19 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head6, align 8, !dbg !118
  br label %cond.end, !dbg !119

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %struct.curl_llist_element* [ %17, %cond.true ], [ %19, %cond.false ], !dbg !120
  %20 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !122
  %next7 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %20, i32 0, i32 2, !dbg !123
  store %struct.curl_llist_element* %cond, %struct.curl_llist_element** %next7, align 8, !dbg !124
  %21 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !125
  %22 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !126
  %prev8 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %22, i32 0, i32 1, !dbg !127
  store %struct.curl_llist_element* %21, %struct.curl_llist_element** %prev8, align 8, !dbg !128
  %23 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !129
  %tobool9 = icmp ne %struct.curl_llist_element* %23, null, !dbg !129
  br i1 %tobool9, label %if.else14, label %if.then10, !dbg !131

if.then10:                                        ; preds = %cond.end
  %24 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !132
  %25 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !134
  %head11 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %25, i32 0, i32 0, !dbg !135
  %26 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head11, align 8, !dbg !135
  %prev12 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %26, i32 0, i32 1, !dbg !136
  store %struct.curl_llist_element* %24, %struct.curl_llist_element** %prev12, align 8, !dbg !137
  %27 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !138
  %28 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !139
  %head13 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %28, i32 0, i32 0, !dbg !140
  store %struct.curl_llist_element* %27, %struct.curl_llist_element** %head13, align 8, !dbg !141
  br label %if.end23, !dbg !142

if.else14:                                        ; preds = %cond.end
  %29 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !143
  %next15 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %29, i32 0, i32 2, !dbg !145
  %30 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next15, align 8, !dbg !145
  %tobool16 = icmp ne %struct.curl_llist_element* %30, null, !dbg !143
  br i1 %tobool16, label %if.then17, label %if.else20, !dbg !146

if.then17:                                        ; preds = %if.else14
  %31 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !147
  %32 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !149
  %next18 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %32, i32 0, i32 2, !dbg !150
  %33 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next18, align 8, !dbg !150
  %prev19 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %33, i32 0, i32 1, !dbg !151
  store %struct.curl_llist_element* %31, %struct.curl_llist_element** %prev19, align 8, !dbg !152
  br label %if.end22, !dbg !153

if.else20:                                        ; preds = %if.else14
  %34 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !154
  %35 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !156
  %tail21 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %35, i32 0, i32 1, !dbg !157
  store %struct.curl_llist_element* %34, %struct.curl_llist_element** %tail21, align 8, !dbg !158
  br label %if.end22

if.end22:                                         ; preds = %if.else20, %if.then17
  br label %if.end23

if.end23:                                         ; preds = %if.end22, %if.then10
  %36 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !159
  %tobool24 = icmp ne %struct.curl_llist_element* %36, null, !dbg !159
  br i1 %tobool24, label %if.then25, label %if.end27, !dbg !161

if.then25:                                        ; preds = %if.end23
  %37 = load %struct.curl_llist_element*, %struct.curl_llist_element** %ne, align 8, !dbg !162
  %38 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !163
  %next26 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %38, i32 0, i32 2, !dbg !164
  store %struct.curl_llist_element* %37, %struct.curl_llist_element** %next26, align 8, !dbg !165
  br label %if.end27, !dbg !163

if.end27:                                         ; preds = %if.then25, %if.end23
  br label %if.end28

if.end28:                                         ; preds = %if.end27, %if.then1
  %39 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !166
  %size29 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %39, i32 0, i32 3, !dbg !167
  %40 = load i64, i64* %size29, align 8, !dbg !168
  %inc = add i64 %40, 1, !dbg !168
  store i64 %inc, i64* %size29, align 8, !dbg !168
  store i32 1, i32* %retval, align 4, !dbg !169
  br label %return, !dbg !169

return:                                           ; preds = %if.end28, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !170
  ret i32 %41, !dbg !170
}

; Function Attrs: nounwind uwtable
define i32 @Curl_llist_remove(%struct.curl_llist* %list, %struct.curl_llist_element* %e, i8* %user) #0 !dbg !36 {
entry:
  %retval = alloca i32, align 4
  %list.addr = alloca %struct.curl_llist*, align 8
  %e.addr = alloca %struct.curl_llist_element*, align 8
  %user.addr = alloca i8*, align 8
  store %struct.curl_llist* %list, %struct.curl_llist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %list.addr, metadata !171, metadata !52), !dbg !172
  store %struct.curl_llist_element* %e, %struct.curl_llist_element** %e.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %e.addr, metadata !173, metadata !52), !dbg !174
  store i8* %user, i8** %user.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %user.addr, metadata !175, metadata !52), !dbg !176
  %0 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !177
  %cmp = icmp eq %struct.curl_llist_element* %0, null, !dbg !179
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !180

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !181
  %size = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %1, i32 0, i32 3, !dbg !183
  %2 = load i64, i64* %size, align 8, !dbg !183
  %cmp1 = icmp eq i64 %2, 0, !dbg !184
  br i1 %cmp1, label %if.then, label %if.end, !dbg !185

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 1, i32* %retval, align 4, !dbg !186
  br label %return, !dbg !186

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !187
  %4 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !189
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %4, i32 0, i32 0, !dbg !190
  %5 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head, align 8, !dbg !190
  %cmp2 = icmp eq %struct.curl_llist_element* %3, %5, !dbg !191
  br i1 %cmp2, label %if.then3, label %if.else10, !dbg !192

if.then3:                                         ; preds = %if.end
  %6 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !193
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %6, i32 0, i32 2, !dbg !195
  %7 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next, align 8, !dbg !195
  %8 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !196
  %head4 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %8, i32 0, i32 0, !dbg !197
  store %struct.curl_llist_element* %7, %struct.curl_llist_element** %head4, align 8, !dbg !198
  %9 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !199
  %head5 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %9, i32 0, i32 0, !dbg !201
  %10 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head5, align 8, !dbg !201
  %cmp6 = icmp eq %struct.curl_llist_element* %10, null, !dbg !202
  br i1 %cmp6, label %if.then7, label %if.else, !dbg !203

if.then7:                                         ; preds = %if.then3
  %11 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !204
  %tail = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %11, i32 0, i32 1, !dbg !205
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %tail, align 8, !dbg !206
  br label %if.end9, !dbg !204

if.else:                                          ; preds = %if.then3
  %12 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !207
  %next8 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %12, i32 0, i32 2, !dbg !208
  %13 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next8, align 8, !dbg !208
  %prev = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %13, i32 0, i32 1, !dbg !209
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %prev, align 8, !dbg !210
  br label %if.end9

if.end9:                                          ; preds = %if.else, %if.then7
  br label %if.end23, !dbg !211

if.else10:                                        ; preds = %if.end
  %14 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !212
  %next11 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %14, i32 0, i32 2, !dbg !214
  %15 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next11, align 8, !dbg !214
  %16 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !215
  %prev12 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %16, i32 0, i32 1, !dbg !216
  %17 = load %struct.curl_llist_element*, %struct.curl_llist_element** %prev12, align 8, !dbg !216
  %next13 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %17, i32 0, i32 2, !dbg !217
  store %struct.curl_llist_element* %15, %struct.curl_llist_element** %next13, align 8, !dbg !218
  %18 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !219
  %next14 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %18, i32 0, i32 2, !dbg !221
  %19 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next14, align 8, !dbg !221
  %tobool = icmp ne %struct.curl_llist_element* %19, null, !dbg !219
  br i1 %tobool, label %if.else18, label %if.then15, !dbg !222

if.then15:                                        ; preds = %if.else10
  %20 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !223
  %prev16 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %20, i32 0, i32 1, !dbg !224
  %21 = load %struct.curl_llist_element*, %struct.curl_llist_element** %prev16, align 8, !dbg !224
  %22 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !225
  %tail17 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %22, i32 0, i32 1, !dbg !226
  store %struct.curl_llist_element* %21, %struct.curl_llist_element** %tail17, align 8, !dbg !227
  br label %if.end22, !dbg !225

if.else18:                                        ; preds = %if.else10
  %23 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !228
  %prev19 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %23, i32 0, i32 1, !dbg !229
  %24 = load %struct.curl_llist_element*, %struct.curl_llist_element** %prev19, align 8, !dbg !229
  %25 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !230
  %next20 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %25, i32 0, i32 2, !dbg !231
  %26 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next20, align 8, !dbg !231
  %prev21 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %26, i32 0, i32 1, !dbg !232
  store %struct.curl_llist_element* %24, %struct.curl_llist_element** %prev21, align 8, !dbg !233
  br label %if.end22

if.end22:                                         ; preds = %if.else18, %if.then15
  br label %if.end23

if.end23:                                         ; preds = %if.end22, %if.end9
  %27 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !234
  %dtor = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %27, i32 0, i32 2, !dbg !235
  %28 = load void (i8*, i8*)*, void (i8*, i8*)** %dtor, align 8, !dbg !235
  %29 = load i8*, i8** %user.addr, align 8, !dbg !236
  %30 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !237
  %ptr = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %30, i32 0, i32 0, !dbg !238
  %31 = load i8*, i8** %ptr, align 8, !dbg !238
  call void %28(i8* %29, i8* %31), !dbg !234
  %32 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !239
  %ptr24 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %32, i32 0, i32 0, !dbg !240
  store i8* null, i8** %ptr24, align 8, !dbg !241
  %33 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !242
  %prev25 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %33, i32 0, i32 1, !dbg !243
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %prev25, align 8, !dbg !244
  %34 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !245
  %next26 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %34, i32 0, i32 2, !dbg !246
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %next26, align 8, !dbg !247
  %35 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !248
  %36 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !248
  %37 = bitcast %struct.curl_llist_element* %36 to i8*, !dbg !248
  call void %35(i8* %37), !dbg !248
  %38 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !249
  %size27 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %38, i32 0, i32 3, !dbg !250
  %39 = load i64, i64* %size27, align 8, !dbg !251
  %dec = add i64 %39, -1, !dbg !251
  store i64 %dec, i64* %size27, align 8, !dbg !251
  store i32 1, i32* %retval, align 4, !dbg !252
  br label %return, !dbg !252

return:                                           ; preds = %if.end23, %if.then
  %40 = load i32, i32* %retval, align 4, !dbg !253
  ret i32 %40, !dbg !253
}

; Function Attrs: nounwind uwtable
define void @Curl_llist_destroy(%struct.curl_llist* %list, i8* %user) #0 !dbg !39 {
entry:
  %list.addr = alloca %struct.curl_llist*, align 8
  %user.addr = alloca i8*, align 8
  store %struct.curl_llist* %list, %struct.curl_llist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %list.addr, metadata !254, metadata !52), !dbg !255
  store i8* %user, i8** %user.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %user.addr, metadata !256, metadata !52), !dbg !257
  %0 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !258
  %tobool = icmp ne %struct.curl_llist* %0, null, !dbg !258
  br i1 %tobool, label %if.then, label %if.end, !dbg !260

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !261

while.cond:                                       ; preds = %while.body, %if.then
  %1 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !263
  %size = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %1, i32 0, i32 3, !dbg !265
  %2 = load i64, i64* %size, align 8, !dbg !265
  %cmp = icmp ugt i64 %2, 0, !dbg !266
  br i1 %cmp, label %while.body, label %while.end, !dbg !267

while.body:                                       ; preds = %while.cond
  %3 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !268
  %4 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !269
  %tail = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %4, i32 0, i32 1, !dbg !270
  %5 = load %struct.curl_llist_element*, %struct.curl_llist_element** %tail, align 8, !dbg !270
  %6 = load i8*, i8** %user.addr, align 8, !dbg !271
  %call = call i32 @Curl_llist_remove(%struct.curl_llist* %3, %struct.curl_llist_element* %5, i8* %6), !dbg !272
  br label %while.cond, !dbg !273

while.end:                                        ; preds = %while.cond
  br label %if.end, !dbg !275

if.end:                                           ; preds = %while.end, %entry
  ret void, !dbg !276
}

; Function Attrs: nounwind uwtable
define i64 @Curl_llist_count(%struct.curl_llist* %list) #0 !dbg !42 {
entry:
  %list.addr = alloca %struct.curl_llist*, align 8
  store %struct.curl_llist* %list, %struct.curl_llist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %list.addr, metadata !277, metadata !52), !dbg !278
  %0 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !279
  %size = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %0, i32 0, i32 3, !dbg !280
  %1 = load i64, i64* %size, align 8, !dbg !280
  ret i64 %1, !dbg !281
}

; Function Attrs: nounwind uwtable
define i32 @Curl_llist_move(%struct.curl_llist* %list, %struct.curl_llist_element* %e, %struct.curl_llist* %to_list, %struct.curl_llist_element* %to_e) #0 !dbg !45 {
entry:
  %retval = alloca i32, align 4
  %list.addr = alloca %struct.curl_llist*, align 8
  %e.addr = alloca %struct.curl_llist_element*, align 8
  %to_list.addr = alloca %struct.curl_llist*, align 8
  %to_e.addr = alloca %struct.curl_llist_element*, align 8
  store %struct.curl_llist* %list, %struct.curl_llist** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %list.addr, metadata !282, metadata !52), !dbg !283
  store %struct.curl_llist_element* %e, %struct.curl_llist_element** %e.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %e.addr, metadata !284, metadata !52), !dbg !285
  store %struct.curl_llist* %to_list, %struct.curl_llist** %to_list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %to_list.addr, metadata !286, metadata !52), !dbg !287
  store %struct.curl_llist_element* %to_e, %struct.curl_llist_element** %to_e.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %to_e.addr, metadata !288, metadata !52), !dbg !289
  %0 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !290
  %cmp = icmp eq %struct.curl_llist_element* %0, null, !dbg !292
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !293

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !294
  %size = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %1, i32 0, i32 3, !dbg !296
  %2 = load i64, i64* %size, align 8, !dbg !296
  %cmp1 = icmp eq i64 %2, 0, !dbg !297
  br i1 %cmp1, label %if.then, label %if.end, !dbg !298

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !299
  br label %return, !dbg !299

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !300
  %4 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !302
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %4, i32 0, i32 0, !dbg !303
  %5 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head, align 8, !dbg !303
  %cmp2 = icmp eq %struct.curl_llist_element* %3, %5, !dbg !304
  br i1 %cmp2, label %if.then3, label %if.else10, !dbg !305

if.then3:                                         ; preds = %if.end
  %6 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !306
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %6, i32 0, i32 2, !dbg !308
  %7 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next, align 8, !dbg !308
  %8 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !309
  %head4 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %8, i32 0, i32 0, !dbg !310
  store %struct.curl_llist_element* %7, %struct.curl_llist_element** %head4, align 8, !dbg !311
  %9 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !312
  %head5 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %9, i32 0, i32 0, !dbg !314
  %10 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head5, align 8, !dbg !314
  %cmp6 = icmp eq %struct.curl_llist_element* %10, null, !dbg !315
  br i1 %cmp6, label %if.then7, label %if.else, !dbg !316

if.then7:                                         ; preds = %if.then3
  %11 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !317
  %tail = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %11, i32 0, i32 1, !dbg !318
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %tail, align 8, !dbg !319
  br label %if.end9, !dbg !317

if.else:                                          ; preds = %if.then3
  %12 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !320
  %next8 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %12, i32 0, i32 2, !dbg !321
  %13 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next8, align 8, !dbg !321
  %prev = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %13, i32 0, i32 1, !dbg !322
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %prev, align 8, !dbg !323
  br label %if.end9

if.end9:                                          ; preds = %if.else, %if.then7
  br label %if.end23, !dbg !324

if.else10:                                        ; preds = %if.end
  %14 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !325
  %next11 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %14, i32 0, i32 2, !dbg !327
  %15 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next11, align 8, !dbg !327
  %16 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !328
  %prev12 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %16, i32 0, i32 1, !dbg !329
  %17 = load %struct.curl_llist_element*, %struct.curl_llist_element** %prev12, align 8, !dbg !329
  %next13 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %17, i32 0, i32 2, !dbg !330
  store %struct.curl_llist_element* %15, %struct.curl_llist_element** %next13, align 8, !dbg !331
  %18 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !332
  %next14 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %18, i32 0, i32 2, !dbg !334
  %19 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next14, align 8, !dbg !334
  %tobool = icmp ne %struct.curl_llist_element* %19, null, !dbg !332
  br i1 %tobool, label %if.else18, label %if.then15, !dbg !335

if.then15:                                        ; preds = %if.else10
  %20 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !336
  %prev16 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %20, i32 0, i32 1, !dbg !337
  %21 = load %struct.curl_llist_element*, %struct.curl_llist_element** %prev16, align 8, !dbg !337
  %22 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !338
  %tail17 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %22, i32 0, i32 1, !dbg !339
  store %struct.curl_llist_element* %21, %struct.curl_llist_element** %tail17, align 8, !dbg !340
  br label %if.end22, !dbg !338

if.else18:                                        ; preds = %if.else10
  %23 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !341
  %prev19 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %23, i32 0, i32 1, !dbg !342
  %24 = load %struct.curl_llist_element*, %struct.curl_llist_element** %prev19, align 8, !dbg !342
  %25 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !343
  %next20 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %25, i32 0, i32 2, !dbg !344
  %26 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next20, align 8, !dbg !344
  %prev21 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %26, i32 0, i32 1, !dbg !345
  store %struct.curl_llist_element* %24, %struct.curl_llist_element** %prev21, align 8, !dbg !346
  br label %if.end22

if.end22:                                         ; preds = %if.else18, %if.then15
  br label %if.end23

if.end23:                                         ; preds = %if.end22, %if.end9
  %27 = load %struct.curl_llist*, %struct.curl_llist** %list.addr, align 8, !dbg !347
  %size24 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %27, i32 0, i32 3, !dbg !348
  %28 = load i64, i64* %size24, align 8, !dbg !349
  %dec = add i64 %28, -1, !dbg !349
  store i64 %dec, i64* %size24, align 8, !dbg !349
  %29 = load %struct.curl_llist*, %struct.curl_llist** %to_list.addr, align 8, !dbg !350
  %size25 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %29, i32 0, i32 3, !dbg !352
  %30 = load i64, i64* %size25, align 8, !dbg !352
  %cmp26 = icmp eq i64 %30, 0, !dbg !353
  br i1 %cmp26, label %if.then27, label %if.else34, !dbg !354

if.then27:                                        ; preds = %if.end23
  %31 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !355
  %32 = load %struct.curl_llist*, %struct.curl_llist** %to_list.addr, align 8, !dbg !357
  %head28 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %32, i32 0, i32 0, !dbg !358
  store %struct.curl_llist_element* %31, %struct.curl_llist_element** %head28, align 8, !dbg !359
  %33 = load %struct.curl_llist*, %struct.curl_llist** %to_list.addr, align 8, !dbg !360
  %head29 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %33, i32 0, i32 0, !dbg !361
  %34 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head29, align 8, !dbg !361
  %prev30 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %34, i32 0, i32 1, !dbg !362
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %prev30, align 8, !dbg !363
  %35 = load %struct.curl_llist*, %struct.curl_llist** %to_list.addr, align 8, !dbg !364
  %head31 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %35, i32 0, i32 0, !dbg !365
  %36 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head31, align 8, !dbg !365
  %next32 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %36, i32 0, i32 2, !dbg !366
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %next32, align 8, !dbg !367
  %37 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !368
  %38 = load %struct.curl_llist*, %struct.curl_llist** %to_list.addr, align 8, !dbg !369
  %tail33 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %38, i32 0, i32 1, !dbg !370
  store %struct.curl_llist_element* %37, %struct.curl_llist_element** %tail33, align 8, !dbg !371
  br label %if.end47, !dbg !372

if.else34:                                        ; preds = %if.end23
  %39 = load %struct.curl_llist_element*, %struct.curl_llist_element** %to_e.addr, align 8, !dbg !373
  %next35 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %39, i32 0, i32 2, !dbg !375
  %40 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next35, align 8, !dbg !375
  %41 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !376
  %next36 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %41, i32 0, i32 2, !dbg !377
  store %struct.curl_llist_element* %40, %struct.curl_llist_element** %next36, align 8, !dbg !378
  %42 = load %struct.curl_llist_element*, %struct.curl_llist_element** %to_e.addr, align 8, !dbg !379
  %43 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !380
  %prev37 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %43, i32 0, i32 1, !dbg !381
  store %struct.curl_llist_element* %42, %struct.curl_llist_element** %prev37, align 8, !dbg !382
  %44 = load %struct.curl_llist_element*, %struct.curl_llist_element** %to_e.addr, align 8, !dbg !383
  %next38 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %44, i32 0, i32 2, !dbg !385
  %45 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next38, align 8, !dbg !385
  %tobool39 = icmp ne %struct.curl_llist_element* %45, null, !dbg !383
  br i1 %tobool39, label %if.then40, label %if.else43, !dbg !386

if.then40:                                        ; preds = %if.else34
  %46 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !387
  %47 = load %struct.curl_llist_element*, %struct.curl_llist_element** %to_e.addr, align 8, !dbg !389
  %next41 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %47, i32 0, i32 2, !dbg !390
  %48 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next41, align 8, !dbg !390
  %prev42 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %48, i32 0, i32 1, !dbg !391
  store %struct.curl_llist_element* %46, %struct.curl_llist_element** %prev42, align 8, !dbg !392
  br label %if.end45, !dbg !393

if.else43:                                        ; preds = %if.else34
  %49 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !394
  %50 = load %struct.curl_llist*, %struct.curl_llist** %to_list.addr, align 8, !dbg !396
  %tail44 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %50, i32 0, i32 1, !dbg !397
  store %struct.curl_llist_element* %49, %struct.curl_llist_element** %tail44, align 8, !dbg !398
  br label %if.end45

if.end45:                                         ; preds = %if.else43, %if.then40
  %51 = load %struct.curl_llist_element*, %struct.curl_llist_element** %e.addr, align 8, !dbg !399
  %52 = load %struct.curl_llist_element*, %struct.curl_llist_element** %to_e.addr, align 8, !dbg !400
  %next46 = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %52, i32 0, i32 2, !dbg !401
  store %struct.curl_llist_element* %51, %struct.curl_llist_element** %next46, align 8, !dbg !402
  br label %if.end47

if.end47:                                         ; preds = %if.end45, %if.then27
  %53 = load %struct.curl_llist*, %struct.curl_llist** %to_list.addr, align 8, !dbg !403
  %size48 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %53, i32 0, i32 3, !dbg !404
  %54 = load i64, i64* %size48, align 8, !dbg !405
  %inc = add i64 %54, 1, !dbg !405
  store i64 %inc, i64* %size48, align 8, !dbg !405
  store i32 1, i32* %retval, align 4, !dbg !406
  br label %return, !dbg !406

return:                                           ; preds = %if.end47, %if.then
  %55 = load i32, i32* %retval, align 4, !dbg !407
  ret i32 %55, !dbg !407
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!48, !49}
!llvm.ident = !{!50}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !30, !36, !39, !42, !45}
!6 = distinct !DISubprogram(name: "Curl_llist_init", scope: !1, file: !1, line: 37, type: !7, isLocal: false, isDefinition: true, scopeLine: 38, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{null, !9, !22}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist", file: !11, line: 37, size: 256, align: 64, elements: !12)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!12 = !{!13, !20, !21, !26}
!13 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !10, file: !11, line: 38, baseType: !14, size: 64, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist_element", file: !11, line: 30, size: 192, align: 64, elements: !16)
!16 = !{!17, !18, !19}
!17 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !15, file: !11, line: 31, baseType: !4, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !15, file: !11, line: 33, baseType: !14, size: 64, align: 64, offset: 64)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !15, file: !11, line: 34, baseType: !14, size: 64, align: 64, offset: 128)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "tail", scope: !10, file: !11, line: 39, baseType: !14, size: 64, align: 64, offset: 64)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !10, file: !11, line: 41, baseType: !22, size: 64, align: 64, offset: 128)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_llist_dtor", file: !11, line: 28, baseType: !23)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DISubroutineType(types: !25)
!25 = !{null, !4, !4}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !10, file: !11, line: 43, baseType: !27, size: 64, align: 64, offset: 192)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !28, line: 62, baseType: !29)
!28 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!29 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!30 = distinct !DISubprogram(name: "Curl_llist_insert_next", scope: !1, file: !1, line: 57, type: !31, isLocal: false, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = !DISubroutineType(types: !32)
!32 = !{!33, !9, !14, !34}
!33 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!36 = distinct !DISubprogram(name: "Curl_llist_remove", scope: !1, file: !1, line: 98, type: !37, isLocal: false, isDefinition: true, scopeLine: 100, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!37 = !DISubroutineType(types: !38)
!38 = !{!33, !9, !14, !4}
!39 = distinct !DISubprogram(name: "Curl_llist_destroy", scope: !1, file: !1, line: 133, type: !40, isLocal: false, isDefinition: true, scopeLine: 134, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!40 = !DISubroutineType(types: !41)
!41 = !{null, !9, !4}
!42 = distinct !DISubprogram(name: "Curl_llist_count", scope: !1, file: !1, line: 142, type: !43, isLocal: false, isDefinition: true, scopeLine: 143, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!43 = !DISubroutineType(types: !44)
!44 = !{!27, !9}
!45 = distinct !DISubprogram(name: "Curl_llist_move", scope: !1, file: !1, line: 150, type: !46, isLocal: false, isDefinition: true, scopeLine: 153, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!46 = !DISubroutineType(types: !47)
!47 = !{!33, !9, !14, !9, !14}
!48 = !{i32 2, !"Dwarf Version", i32 4}
!49 = !{i32 2, !"Debug Info Version", i32 3}
!50 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!51 = !DILocalVariable(name: "l", arg: 1, scope: !6, file: !1, line: 37, type: !9)
!52 = !DIExpression()
!53 = !DILocation(line: 37, column: 36, scope: !6)
!54 = !DILocalVariable(name: "dtor", arg: 2, scope: !6, file: !1, line: 37, type: !22)
!55 = !DILocation(line: 37, column: 55, scope: !6)
!56 = !DILocation(line: 39, column: 3, scope: !6)
!57 = !DILocation(line: 39, column: 6, scope: !6)
!58 = !DILocation(line: 39, column: 11, scope: !6)
!59 = !DILocation(line: 40, column: 13, scope: !6)
!60 = !DILocation(line: 40, column: 3, scope: !6)
!61 = !DILocation(line: 40, column: 6, scope: !6)
!62 = !DILocation(line: 40, column: 11, scope: !6)
!63 = !DILocation(line: 41, column: 3, scope: !6)
!64 = !DILocation(line: 41, column: 6, scope: !6)
!65 = !DILocation(line: 41, column: 11, scope: !6)
!66 = !DILocation(line: 42, column: 3, scope: !6)
!67 = !DILocation(line: 42, column: 6, scope: !6)
!68 = !DILocation(line: 42, column: 11, scope: !6)
!69 = !DILocation(line: 43, column: 1, scope: !6)
!70 = !DILocalVariable(name: "list", arg: 1, scope: !30, file: !1, line: 57, type: !9)
!71 = !DILocation(line: 57, column: 43, scope: !30)
!72 = !DILocalVariable(name: "e", arg: 2, scope: !30, file: !1, line: 57, type: !14)
!73 = !DILocation(line: 57, column: 76, scope: !30)
!74 = !DILocalVariable(name: "p", arg: 3, scope: !30, file: !1, line: 58, type: !34)
!75 = !DILocation(line: 58, column: 36, scope: !30)
!76 = !DILocalVariable(name: "ne", scope: !30, file: !1, line: 60, type: !14)
!77 = !DILocation(line: 60, column: 30, scope: !30)
!78 = !DILocation(line: 60, column: 35, scope: !30)
!79 = !DILocation(line: 61, column: 7, scope: !80)
!80 = distinct !DILexicalBlock(scope: !30, file: !1, line: 61, column: 6)
!81 = !DILocation(line: 61, column: 6, scope: !30)
!82 = !DILocation(line: 62, column: 5, scope: !80)
!83 = !DILocation(line: 64, column: 22, scope: !30)
!84 = !DILocation(line: 64, column: 3, scope: !30)
!85 = !DILocation(line: 64, column: 7, scope: !30)
!86 = !DILocation(line: 64, column: 11, scope: !30)
!87 = !DILocation(line: 65, column: 6, scope: !88)
!88 = distinct !DILexicalBlock(scope: !30, file: !1, line: 65, column: 6)
!89 = !DILocation(line: 65, column: 12, scope: !88)
!90 = !DILocation(line: 65, column: 17, scope: !88)
!91 = !DILocation(line: 65, column: 6, scope: !30)
!92 = !DILocation(line: 66, column: 18, scope: !93)
!93 = distinct !DILexicalBlock(scope: !88, file: !1, line: 65, column: 23)
!94 = !DILocation(line: 66, column: 5, scope: !93)
!95 = !DILocation(line: 66, column: 11, scope: !93)
!96 = !DILocation(line: 66, column: 16, scope: !93)
!97 = !DILocation(line: 67, column: 5, scope: !93)
!98 = !DILocation(line: 67, column: 11, scope: !93)
!99 = !DILocation(line: 67, column: 17, scope: !93)
!100 = !DILocation(line: 67, column: 22, scope: !93)
!101 = !DILocation(line: 68, column: 5, scope: !93)
!102 = !DILocation(line: 68, column: 11, scope: !93)
!103 = !DILocation(line: 68, column: 17, scope: !93)
!104 = !DILocation(line: 68, column: 22, scope: !93)
!105 = !DILocation(line: 69, column: 18, scope: !93)
!106 = !DILocation(line: 69, column: 5, scope: !93)
!107 = !DILocation(line: 69, column: 11, scope: !93)
!108 = !DILocation(line: 69, column: 16, scope: !93)
!109 = !DILocation(line: 70, column: 3, scope: !93)
!110 = !DILocation(line: 73, column: 16, scope: !111)
!111 = distinct !DILexicalBlock(scope: !88, file: !1, line: 71, column: 8)
!112 = !DILocation(line: 73, column: 18, scope: !113)
!113 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 1)
!114 = !DILocation(line: 73, column: 21, scope: !113)
!115 = !DILocation(line: 73, column: 16, scope: !113)
!116 = !DILocation(line: 73, column: 26, scope: !117)
!117 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 2)
!118 = !DILocation(line: 73, column: 32, scope: !117)
!119 = !DILocation(line: 73, column: 16, scope: !117)
!120 = !DILocation(line: 73, column: 16, scope: !121)
!121 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 3)
!122 = !DILocation(line: 73, column: 5, scope: !121)
!123 = !DILocation(line: 73, column: 9, scope: !121)
!124 = !DILocation(line: 73, column: 14, scope: !121)
!125 = !DILocation(line: 74, column: 16, scope: !111)
!126 = !DILocation(line: 74, column: 5, scope: !111)
!127 = !DILocation(line: 74, column: 9, scope: !111)
!128 = !DILocation(line: 74, column: 14, scope: !111)
!129 = !DILocation(line: 75, column: 9, scope: !130)
!130 = distinct !DILexicalBlock(scope: !111, file: !1, line: 75, column: 8)
!131 = !DILocation(line: 75, column: 8, scope: !111)
!132 = !DILocation(line: 76, column: 26, scope: !133)
!133 = distinct !DILexicalBlock(scope: !130, file: !1, line: 75, column: 12)
!134 = !DILocation(line: 76, column: 7, scope: !133)
!135 = !DILocation(line: 76, column: 13, scope: !133)
!136 = !DILocation(line: 76, column: 19, scope: !133)
!137 = !DILocation(line: 76, column: 24, scope: !133)
!138 = !DILocation(line: 77, column: 20, scope: !133)
!139 = !DILocation(line: 77, column: 7, scope: !133)
!140 = !DILocation(line: 77, column: 13, scope: !133)
!141 = !DILocation(line: 77, column: 18, scope: !133)
!142 = !DILocation(line: 78, column: 5, scope: !133)
!143 = !DILocation(line: 79, column: 13, scope: !144)
!144 = distinct !DILexicalBlock(scope: !130, file: !1, line: 79, column: 13)
!145 = !DILocation(line: 79, column: 16, scope: !144)
!146 = !DILocation(line: 79, column: 13, scope: !130)
!147 = !DILocation(line: 80, column: 23, scope: !148)
!148 = distinct !DILexicalBlock(scope: !144, file: !1, line: 79, column: 22)
!149 = !DILocation(line: 80, column: 7, scope: !148)
!150 = !DILocation(line: 80, column: 10, scope: !148)
!151 = !DILocation(line: 80, column: 16, scope: !148)
!152 = !DILocation(line: 80, column: 21, scope: !148)
!153 = !DILocation(line: 81, column: 5, scope: !148)
!154 = !DILocation(line: 83, column: 20, scope: !155)
!155 = distinct !DILexicalBlock(scope: !144, file: !1, line: 82, column: 10)
!156 = !DILocation(line: 83, column: 7, scope: !155)
!157 = !DILocation(line: 83, column: 13, scope: !155)
!158 = !DILocation(line: 83, column: 18, scope: !155)
!159 = !DILocation(line: 85, column: 8, scope: !160)
!160 = distinct !DILexicalBlock(scope: !111, file: !1, line: 85, column: 8)
!161 = !DILocation(line: 85, column: 8, scope: !111)
!162 = !DILocation(line: 86, column: 17, scope: !160)
!163 = !DILocation(line: 86, column: 7, scope: !160)
!164 = !DILocation(line: 86, column: 10, scope: !160)
!165 = !DILocation(line: 86, column: 15, scope: !160)
!166 = !DILocation(line: 89, column: 5, scope: !30)
!167 = !DILocation(line: 89, column: 11, scope: !30)
!168 = !DILocation(line: 89, column: 3, scope: !30)
!169 = !DILocation(line: 91, column: 3, scope: !30)
!170 = !DILocation(line: 92, column: 1, scope: !30)
!171 = !DILocalVariable(name: "list", arg: 1, scope: !36, file: !1, line: 98, type: !9)
!172 = !DILocation(line: 98, column: 38, scope: !36)
!173 = !DILocalVariable(name: "e", arg: 2, scope: !36, file: !1, line: 98, type: !14)
!174 = !DILocation(line: 98, column: 71, scope: !36)
!175 = !DILocalVariable(name: "user", arg: 3, scope: !36, file: !1, line: 99, type: !4)
!176 = !DILocation(line: 99, column: 25, scope: !36)
!177 = !DILocation(line: 101, column: 6, scope: !178)
!178 = distinct !DILexicalBlock(scope: !36, file: !1, line: 101, column: 6)
!179 = !DILocation(line: 101, column: 8, scope: !178)
!180 = !DILocation(line: 101, column: 16, scope: !178)
!181 = !DILocation(line: 101, column: 19, scope: !182)
!182 = !DILexicalBlockFile(scope: !178, file: !1, discriminator: 1)
!183 = !DILocation(line: 101, column: 25, scope: !182)
!184 = !DILocation(line: 101, column: 30, scope: !182)
!185 = !DILocation(line: 101, column: 6, scope: !182)
!186 = !DILocation(line: 102, column: 5, scope: !178)
!187 = !DILocation(line: 104, column: 6, scope: !188)
!188 = distinct !DILexicalBlock(scope: !36, file: !1, line: 104, column: 6)
!189 = !DILocation(line: 104, column: 11, scope: !188)
!190 = !DILocation(line: 104, column: 17, scope: !188)
!191 = !DILocation(line: 104, column: 8, scope: !188)
!192 = !DILocation(line: 104, column: 6, scope: !36)
!193 = !DILocation(line: 105, column: 18, scope: !194)
!194 = distinct !DILexicalBlock(scope: !188, file: !1, line: 104, column: 23)
!195 = !DILocation(line: 105, column: 21, scope: !194)
!196 = !DILocation(line: 105, column: 5, scope: !194)
!197 = !DILocation(line: 105, column: 11, scope: !194)
!198 = !DILocation(line: 105, column: 16, scope: !194)
!199 = !DILocation(line: 107, column: 8, scope: !200)
!200 = distinct !DILexicalBlock(scope: !194, file: !1, line: 107, column: 8)
!201 = !DILocation(line: 107, column: 14, scope: !200)
!202 = !DILocation(line: 107, column: 19, scope: !200)
!203 = !DILocation(line: 107, column: 8, scope: !194)
!204 = !DILocation(line: 108, column: 7, scope: !200)
!205 = !DILocation(line: 108, column: 13, scope: !200)
!206 = !DILocation(line: 108, column: 18, scope: !200)
!207 = !DILocation(line: 110, column: 7, scope: !200)
!208 = !DILocation(line: 110, column: 10, scope: !200)
!209 = !DILocation(line: 110, column: 16, scope: !200)
!210 = !DILocation(line: 110, column: 21, scope: !200)
!211 = !DILocation(line: 111, column: 3, scope: !194)
!212 = !DILocation(line: 113, column: 21, scope: !213)
!213 = distinct !DILexicalBlock(scope: !188, file: !1, line: 112, column: 8)
!214 = !DILocation(line: 113, column: 24, scope: !213)
!215 = !DILocation(line: 113, column: 5, scope: !213)
!216 = !DILocation(line: 113, column: 8, scope: !213)
!217 = !DILocation(line: 113, column: 14, scope: !213)
!218 = !DILocation(line: 113, column: 19, scope: !213)
!219 = !DILocation(line: 114, column: 9, scope: !220)
!220 = distinct !DILexicalBlock(scope: !213, file: !1, line: 114, column: 8)
!221 = !DILocation(line: 114, column: 12, scope: !220)
!222 = !DILocation(line: 114, column: 8, scope: !213)
!223 = !DILocation(line: 115, column: 20, scope: !220)
!224 = !DILocation(line: 115, column: 23, scope: !220)
!225 = !DILocation(line: 115, column: 7, scope: !220)
!226 = !DILocation(line: 115, column: 13, scope: !220)
!227 = !DILocation(line: 115, column: 18, scope: !220)
!228 = !DILocation(line: 117, column: 23, scope: !220)
!229 = !DILocation(line: 117, column: 26, scope: !220)
!230 = !DILocation(line: 117, column: 7, scope: !220)
!231 = !DILocation(line: 117, column: 10, scope: !220)
!232 = !DILocation(line: 117, column: 16, scope: !220)
!233 = !DILocation(line: 117, column: 21, scope: !220)
!234 = !DILocation(line: 120, column: 3, scope: !36)
!235 = !DILocation(line: 120, column: 9, scope: !36)
!236 = !DILocation(line: 120, column: 14, scope: !36)
!237 = !DILocation(line: 120, column: 20, scope: !36)
!238 = !DILocation(line: 120, column: 23, scope: !36)
!239 = !DILocation(line: 122, column: 3, scope: !36)
!240 = !DILocation(line: 122, column: 6, scope: !36)
!241 = !DILocation(line: 122, column: 11, scope: !36)
!242 = !DILocation(line: 123, column: 3, scope: !36)
!243 = !DILocation(line: 123, column: 6, scope: !36)
!244 = !DILocation(line: 123, column: 11, scope: !36)
!245 = !DILocation(line: 124, column: 3, scope: !36)
!246 = !DILocation(line: 124, column: 6, scope: !36)
!247 = !DILocation(line: 124, column: 11, scope: !36)
!248 = !DILocation(line: 126, column: 3, scope: !36)
!249 = !DILocation(line: 127, column: 5, scope: !36)
!250 = !DILocation(line: 127, column: 11, scope: !36)
!251 = !DILocation(line: 127, column: 3, scope: !36)
!252 = !DILocation(line: 129, column: 3, scope: !36)
!253 = !DILocation(line: 130, column: 1, scope: !36)
!254 = !DILocalVariable(name: "list", arg: 1, scope: !39, file: !1, line: 133, type: !9)
!255 = !DILocation(line: 133, column: 39, scope: !39)
!256 = !DILocalVariable(name: "user", arg: 2, scope: !39, file: !1, line: 133, type: !4)
!257 = !DILocation(line: 133, column: 51, scope: !39)
!258 = !DILocation(line: 135, column: 6, scope: !259)
!259 = distinct !DILexicalBlock(scope: !39, file: !1, line: 135, column: 6)
!260 = !DILocation(line: 135, column: 6, scope: !39)
!261 = !DILocation(line: 136, column: 5, scope: !262)
!262 = distinct !DILexicalBlock(scope: !259, file: !1, line: 135, column: 12)
!263 = !DILocation(line: 136, column: 11, scope: !264)
!264 = !DILexicalBlockFile(scope: !262, file: !1, discriminator: 1)
!265 = !DILocation(line: 136, column: 17, scope: !264)
!266 = !DILocation(line: 136, column: 22, scope: !264)
!267 = !DILocation(line: 136, column: 5, scope: !264)
!268 = !DILocation(line: 137, column: 25, scope: !262)
!269 = !DILocation(line: 137, column: 31, scope: !262)
!270 = !DILocation(line: 137, column: 37, scope: !262)
!271 = !DILocation(line: 137, column: 43, scope: !262)
!272 = !DILocation(line: 137, column: 7, scope: !262)
!273 = !DILocation(line: 136, column: 5, scope: !274)
!274 = !DILexicalBlockFile(scope: !262, file: !1, discriminator: 2)
!275 = !DILocation(line: 138, column: 3, scope: !262)
!276 = !DILocation(line: 139, column: 1, scope: !39)
!277 = !DILocalVariable(name: "list", arg: 1, scope: !42, file: !1, line: 142, type: !9)
!278 = !DILocation(line: 142, column: 37, scope: !42)
!279 = !DILocation(line: 144, column: 10, scope: !42)
!280 = !DILocation(line: 144, column: 16, scope: !42)
!281 = !DILocation(line: 144, column: 3, scope: !42)
!282 = !DILocalVariable(name: "list", arg: 1, scope: !45, file: !1, line: 150, type: !9)
!283 = !DILocation(line: 150, column: 40, scope: !45)
!284 = !DILocalVariable(name: "e", arg: 2, scope: !45, file: !1, line: 150, type: !14)
!285 = !DILocation(line: 150, column: 73, scope: !45)
!286 = !DILocalVariable(name: "to_list", arg: 3, scope: !45, file: !1, line: 151, type: !9)
!287 = !DILocation(line: 151, column: 40, scope: !45)
!288 = !DILocalVariable(name: "to_e", arg: 4, scope: !45, file: !1, line: 152, type: !14)
!289 = !DILocation(line: 152, column: 48, scope: !45)
!290 = !DILocation(line: 155, column: 6, scope: !291)
!291 = distinct !DILexicalBlock(scope: !45, file: !1, line: 155, column: 6)
!292 = !DILocation(line: 155, column: 8, scope: !291)
!293 = !DILocation(line: 155, column: 16, scope: !291)
!294 = !DILocation(line: 155, column: 19, scope: !295)
!295 = !DILexicalBlockFile(scope: !291, file: !1, discriminator: 1)
!296 = !DILocation(line: 155, column: 25, scope: !295)
!297 = !DILocation(line: 155, column: 30, scope: !295)
!298 = !DILocation(line: 155, column: 6, scope: !295)
!299 = !DILocation(line: 156, column: 5, scope: !291)
!300 = !DILocation(line: 158, column: 6, scope: !301)
!301 = distinct !DILexicalBlock(scope: !45, file: !1, line: 158, column: 6)
!302 = !DILocation(line: 158, column: 11, scope: !301)
!303 = !DILocation(line: 158, column: 17, scope: !301)
!304 = !DILocation(line: 158, column: 8, scope: !301)
!305 = !DILocation(line: 158, column: 6, scope: !45)
!306 = !DILocation(line: 159, column: 18, scope: !307)
!307 = distinct !DILexicalBlock(scope: !301, file: !1, line: 158, column: 23)
!308 = !DILocation(line: 159, column: 21, scope: !307)
!309 = !DILocation(line: 159, column: 5, scope: !307)
!310 = !DILocation(line: 159, column: 11, scope: !307)
!311 = !DILocation(line: 159, column: 16, scope: !307)
!312 = !DILocation(line: 161, column: 8, scope: !313)
!313 = distinct !DILexicalBlock(scope: !307, file: !1, line: 161, column: 8)
!314 = !DILocation(line: 161, column: 14, scope: !313)
!315 = !DILocation(line: 161, column: 19, scope: !313)
!316 = !DILocation(line: 161, column: 8, scope: !307)
!317 = !DILocation(line: 162, column: 7, scope: !313)
!318 = !DILocation(line: 162, column: 13, scope: !313)
!319 = !DILocation(line: 162, column: 18, scope: !313)
!320 = !DILocation(line: 164, column: 7, scope: !313)
!321 = !DILocation(line: 164, column: 10, scope: !313)
!322 = !DILocation(line: 164, column: 16, scope: !313)
!323 = !DILocation(line: 164, column: 21, scope: !313)
!324 = !DILocation(line: 165, column: 3, scope: !307)
!325 = !DILocation(line: 167, column: 21, scope: !326)
!326 = distinct !DILexicalBlock(scope: !301, file: !1, line: 166, column: 8)
!327 = !DILocation(line: 167, column: 24, scope: !326)
!328 = !DILocation(line: 167, column: 5, scope: !326)
!329 = !DILocation(line: 167, column: 8, scope: !326)
!330 = !DILocation(line: 167, column: 14, scope: !326)
!331 = !DILocation(line: 167, column: 19, scope: !326)
!332 = !DILocation(line: 168, column: 9, scope: !333)
!333 = distinct !DILexicalBlock(scope: !326, file: !1, line: 168, column: 8)
!334 = !DILocation(line: 168, column: 12, scope: !333)
!335 = !DILocation(line: 168, column: 8, scope: !326)
!336 = !DILocation(line: 169, column: 20, scope: !333)
!337 = !DILocation(line: 169, column: 23, scope: !333)
!338 = !DILocation(line: 169, column: 7, scope: !333)
!339 = !DILocation(line: 169, column: 13, scope: !333)
!340 = !DILocation(line: 169, column: 18, scope: !333)
!341 = !DILocation(line: 171, column: 23, scope: !333)
!342 = !DILocation(line: 171, column: 26, scope: !333)
!343 = !DILocation(line: 171, column: 7, scope: !333)
!344 = !DILocation(line: 171, column: 10, scope: !333)
!345 = !DILocation(line: 171, column: 16, scope: !333)
!346 = !DILocation(line: 171, column: 21, scope: !333)
!347 = !DILocation(line: 174, column: 5, scope: !45)
!348 = !DILocation(line: 174, column: 11, scope: !45)
!349 = !DILocation(line: 174, column: 3, scope: !45)
!350 = !DILocation(line: 177, column: 6, scope: !351)
!351 = distinct !DILexicalBlock(scope: !45, file: !1, line: 177, column: 6)
!352 = !DILocation(line: 177, column: 15, scope: !351)
!353 = !DILocation(line: 177, column: 20, scope: !351)
!354 = !DILocation(line: 177, column: 6, scope: !45)
!355 = !DILocation(line: 178, column: 21, scope: !356)
!356 = distinct !DILexicalBlock(scope: !351, file: !1, line: 177, column: 26)
!357 = !DILocation(line: 178, column: 5, scope: !356)
!358 = !DILocation(line: 178, column: 14, scope: !356)
!359 = !DILocation(line: 178, column: 19, scope: !356)
!360 = !DILocation(line: 179, column: 5, scope: !356)
!361 = !DILocation(line: 179, column: 14, scope: !356)
!362 = !DILocation(line: 179, column: 20, scope: !356)
!363 = !DILocation(line: 179, column: 25, scope: !356)
!364 = !DILocation(line: 180, column: 5, scope: !356)
!365 = !DILocation(line: 180, column: 14, scope: !356)
!366 = !DILocation(line: 180, column: 20, scope: !356)
!367 = !DILocation(line: 180, column: 25, scope: !356)
!368 = !DILocation(line: 181, column: 21, scope: !356)
!369 = !DILocation(line: 181, column: 5, scope: !356)
!370 = !DILocation(line: 181, column: 14, scope: !356)
!371 = !DILocation(line: 181, column: 19, scope: !356)
!372 = !DILocation(line: 182, column: 3, scope: !356)
!373 = !DILocation(line: 184, column: 15, scope: !374)
!374 = distinct !DILexicalBlock(scope: !351, file: !1, line: 183, column: 8)
!375 = !DILocation(line: 184, column: 21, scope: !374)
!376 = !DILocation(line: 184, column: 5, scope: !374)
!377 = !DILocation(line: 184, column: 8, scope: !374)
!378 = !DILocation(line: 184, column: 13, scope: !374)
!379 = !DILocation(line: 185, column: 15, scope: !374)
!380 = !DILocation(line: 185, column: 5, scope: !374)
!381 = !DILocation(line: 185, column: 8, scope: !374)
!382 = !DILocation(line: 185, column: 13, scope: !374)
!383 = !DILocation(line: 186, column: 8, scope: !384)
!384 = distinct !DILexicalBlock(scope: !374, file: !1, line: 186, column: 8)
!385 = !DILocation(line: 186, column: 14, scope: !384)
!386 = !DILocation(line: 186, column: 8, scope: !374)
!387 = !DILocation(line: 187, column: 26, scope: !388)
!388 = distinct !DILexicalBlock(scope: !384, file: !1, line: 186, column: 20)
!389 = !DILocation(line: 187, column: 7, scope: !388)
!390 = !DILocation(line: 187, column: 13, scope: !388)
!391 = !DILocation(line: 187, column: 19, scope: !388)
!392 = !DILocation(line: 187, column: 24, scope: !388)
!393 = !DILocation(line: 188, column: 5, scope: !388)
!394 = !DILocation(line: 190, column: 23, scope: !395)
!395 = distinct !DILexicalBlock(scope: !384, file: !1, line: 189, column: 10)
!396 = !DILocation(line: 190, column: 7, scope: !395)
!397 = !DILocation(line: 190, column: 16, scope: !395)
!398 = !DILocation(line: 190, column: 21, scope: !395)
!399 = !DILocation(line: 192, column: 18, scope: !374)
!400 = !DILocation(line: 192, column: 5, scope: !374)
!401 = !DILocation(line: 192, column: 11, scope: !374)
!402 = !DILocation(line: 192, column: 16, scope: !374)
!403 = !DILocation(line: 195, column: 5, scope: !45)
!404 = !DILocation(line: 195, column: 14, scope: !45)
!405 = !DILocation(line: 195, column: 3, scope: !45)
!406 = !DILocation(line: 197, column: 3, scope: !45)
!407 = !DILocation(line: 198, column: 1, scope: !45)
